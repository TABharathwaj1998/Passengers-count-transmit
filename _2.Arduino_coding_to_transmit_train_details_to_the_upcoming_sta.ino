         /* Arduino coding to transmit train details to the upcoming station */
#include<Wire.h>
#include<EEPROM.h>
#include<SoftwareSerial.h>
SoftwareSerial HC12(10,11);
#include "SevSeg.h"
SevSeg sevseg;
int sensorpin1=0;
int sensorpin2=1;
int sensorpin=2;
#define LSRSND1 22
#define LSRSND2 23
#define LSRRCVE1 24
#define LSRRCVE2 25
#define PIR 26
#define LSRRCVE 27
#define TL1 28
#define TL2 29
#define CNTRCVD 30
#define SETPIN 43
int P1, P2, TD;
static long int
d=0,details=0,counter=0,c[50],send=0,S=0,receive=0,Check=0,coach1=0,coach2
=0,coach=0,Tno=0,tno=0,tno1=0,tno2=0,i=0,j=0,k=0,X=0,lock=0,t=0,r=0,Error=0,time=0,Fix=0;
int stno[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
int pltfmno[]={1,2};
static int s=0,a=0,flag=0;
static int DA=0,Status=0,Sts=0,Step=0,wait=0;
void setup()
{
HC12.begin(9600);
Wire.begin(1);
pinMode(LSRRCVE,INPUT);
pinMode(TL1,OUTPUT);
pinMode(TL2,OUTPUT);
pinMode(LSRSND1,OUTPUT);
pinMode(LSRRCVE1,INPUT);
pinMode(LSRSND2,OUTPUT);
pinMode(LSRRCVE2,INPUT);
pinMode(PIR,INPUT);
pinMode(CNTRCVD,INPUT);
pinMode(SETPIN,OUTPUT);
pinMode(31,OUTPUT);
pinMode(32,OUTPUT);
pinMode(33,OUTPUT);
pinMode(34,OUTPUT);
pinMode(35,OUTPUT);
pinMode(36,OUTPUT);
pinMode(37,OUTPUT);
pinMode(38,OUTPUT);
pinMode(39,OUTPUT);
pinMode(40,OUTPUT);
pinMode(41,OUTPUT);
pinMode(42,OUTPUT);
byte numDigits = 4;
byte digitPins[] = {10,11,12,13};
byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
bool resistorsOnSegments = true;
byte hardwareConfig = COMMON_CATHODE;
sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins,
resistorsOnSegments);
sevseg.setBrightness(100);
DA=EEPROM.read(1);
Status=EEPROM.read(2);
X=EEPROM.read(3);
Check=EEPROM.read(4);
lock=EEPROM.read(5);
Step=EEPROM.read(6);
tno1=EEPROM.read(7);
coach1=EEPROM.read(8);
Tno=EEPROM.read(9);
coach=EEPROM.read(10);
Fix=EEPROM.read(11);
r=EEPROM.read(12);
receive=EEPROM.read(13);
wait=EEPROM.read(14);
t=EEPROM.read(15);
send=EEPROM.read(16);
Error=EEPROM.read(17);
time=EEPROM.read(18);
S=EEPROM.read(19);
tno=EEPROM.read(20);
i=EEPROM.read(21);
j=EEPROM.read(22);
flag=EEPROM.read(23);
coach2=EEPROM.read(24);
tno2=EEPROM.read(25);
counter=EEPROM.read(26);
details=EEPROM.read(27);
d=EEPROM.read(28);
Sts=EEPROM.read(29);
}
void loop()
{
if(Fix==0&&Step==0)
{
if(digitalRead(PIR)==1&&Status==2)
{
DA==0;
EEPROM.write(1,DA);
Status==0;
EEPROM.write(2,Status);
X==0;
EEPROM.write(3,X);
Check==0;
EEPROM.write(4,Check);
digitalWrite(TL1,LOW);
digitalWrite(TL2,LOW);
}
TD=analogRead(sensorpin); /* P1 and P2 stands for Force Sensing Resistor fixed
at the side of Gangway connectors. */
P1=analogRead(sensorpin);
P2=analogRead(sensorpin);
if(P1<20&&P2<20) /* If both lower...... */
{
lock==0; /* .......lock becomes zero. */
EEPROM.write(5,lock);
Step==1;
EEPROM.write(6,Step);
tno1==0;
EEPROM.write(7,tno1);
coach1==0;
EEPROM.write(8,coach1);
}
else if(P1<20&&P2>20&&tno1==0) /* 1st compartment of Train number "Tno" 13
which is used by "coach1" variable will be done if P2 is higher than 20, P1 lower
than 20 and tno1 value is zero. */
{
Tno==13;
EEPROM.write(9,Tno);
coach1==Tno;
EEPROM.write(8,coach1);
lock==0;
EEPROM.write(5,lock);
Step==1;
EEPROM.write(6,Step);
}
else if(P1<20&&P2>20&&tno1!=0&&Error==0&&t==0) /* Same as above loop but
takes place only when Error and t is zero and train number tno1 is not zero */
{
Tno==13;
EEPROM.write(9,Tno);
coach1==1;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
lock==1;
EEPROM.write(5,lock);
Step==2; /* Step 2 to obtain station code & platform number. */
EEPROM.write(6,Step);
} /* For Train numbers in even, P2 will be lower and P1 will be higher. */
/* In case higher the value of sensors, then zero is the Train and Coach number as
shown in loop below. */
else if(P1>20&&P2>20&&lock==0)
{
tno1==0;
EEPROM.write(7,tno1);
coach1==0;
EEPROM.write(8,coach1);
lock==0;
EEPROM.write(5,lock);
Step==1;
EEPROM.write(6,Step);
}
else if(P1>20&&P2>20&&lock==1&&Error==0&&t==0)
{
coach1==0;
EEPROM.write(8,coach1);
Step==2;
EEPROM.write(6,Step);
}
else
{
Step==2;
EEPROM.write(6,Step);
}
Fix==1;
EEPROM.write(11,Fix);
}
else
if(Step==1&&P1>20&&(Fix==1||Fix==0)&&(Check==0||Check==1)&&(coach1==0
||t==0)&&r!=2) /* Receiver will receive light only when coach1 value is 0. */
{
Fix==1;
EEPROM.write(11,Fix);
r==1; /* After condition satisfies, r becomes 1 indicating receiver 1............*/
EEPROM.write(12,r);
digitalWrite(LSRSND1,HIGH); /* ......and sends light to transmitter that receiver
is in ACTIVE mode. */
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
while(Check==0) /* Initially this loop verifies whether Check is 0.*/
{
if(digitalRead(LSRRCVE1)==1) /* Then receiver checks whether it detects Laser
from Transmitter. If condition satisfies.......... */
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
Check==1;
EEPROM.write(4,Check);
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1&&coach1<13)
{
coach1=coach1+2;
EEPROM.write(8,coach1);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
receive=receive*0;
EEPROM.write(13,receive);
r==0;
EEPROM.write(12,r);
Check==0;
EEPROM.write(13,Check);
}
else if(digitalRead(LSRRCVE1)==1&&coach1<13&&receive==0)
{
coach1=coach1+1;
EEPROM.write(8,coach1);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
receive=receive*0;
EEPROM.write(13,receive);
r==0;
EEPROM.write(12,r);
Check==0;
EEPROM.write(4,Check);
Fix==0;
EEPROM.write(11,Fix);
}
else if(digitalRead(LSRRCVE1)==1&&coach1>12)
{
Tno=coach1+1;
EEPROM.write(9,Tno);
receive=receive*0;
EEPROM.write(13,receive);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
r==0;
EEPROM.write(12,r);
Check==0;
EEPROM.write(4,Check);
}
else if(digitalRead(LSRRCVE1)==1&&coach1>12&&receive==0)
{
Tno=coach1;
EEPROM.write(9,Tno);
receive=receive*0;
EEPROM.write(13,receive);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
r==0;
EEPROM.write(12,r);
Check==0;
EEPROM.write(4,Check);
}
else
{
}
}
else
{
Check==1;
EEPROM.write(4,Check);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
}
}
else
{
receive=receive+1; /* ........., then receive is incremented and Receiver
sends light to the transmitter two times indicating confirmation. */
EEPROM.write(13,receive);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50); /* Laser light blinking always takes place for transmission
with 50 milliseconds delay in between. LSR means Laser, SND means Send RCVE
means Receive. */
if(digitalRead(LSRRCVE1)==1) /* If the receiver detects light two times with
delay of 50 milliseconds in between....... */
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
Check==1; /* .........then Check becomes 1 so that Receiver will
check whether the value received is correct. */
EEPROM.write(4,Check);
wait=wait*0;
EEPROM.write(14,wait);
digitalWrite(LSRSND1,HIGH); /* Receiver sends light twice for making the
sender change its Check value as 1. */
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
}
}
}
}
else /* After transmission to sender indicating ACTIVE mode, if the receiver
doesn't detects light,.......... */
{
while(wait<=1000) /* ..........then wait value is incremented until....... */
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
Check==1;
EEPROM.write(4,Check);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
} /* ........it detects light for one time thus moving towards loop() function and
continues without incrementing the receiver value or detects light for two times so
that “Check" value becomes one. */
else
{
loop();
break;
}
}
else
{
if(wait=1000)
{
wait==0;
EEPROM.write(14,wait);
}
else
{
wait++;
EEPROM.write(14,wait);
}
}
}
}
}
while(digitalRead(LSRRCVE1)==0&&Check==1&&receive>=0) /* After Check
value becomes 1,..... */
{ /* .......the Receiver sends the laser light to the transmitter thrice. */
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
/* Then the receiver receives light from transmitter for three times so that
"receive" & "coach1" is decremented and incremented once respectively. If
receives light for four times.......*/
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1&&coach1<13) /* ....then receiver will take the
value as "coach1" value indicating the number of the particular compartment if
value is less than 13 due to 12 coaches in Suburban trains of India for example. If
coach1 is greater than 12, then it is taken as Train number value tno1*/
{
coach1=coach1+2; /* The sender will send it's own coach number. For
instance if coach number is 2, then four times transmission takes place during the
2nd time light detection for three times because transmitter receives “send" value
immediately after three times light detection and then sends light thrice to
receiver to make “receive" value decrease once. This one step ahead process of
transmitter makes the receiver value increment the value of 2 also after four time
detection. One more time increment will make coach number as 3 if sender has
coach number 2. */
EEPROM.write(8,coach1);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
receive=receive*0;
EEPROM.write(13,receive);
r==0;
EEPROM.write(12,r);
Check==0;
EEPROM.write(4,Check);
}
else if(digitalRead(LSRRCVE1)==1&&coach1<13&&receive==0) /* If “receive"
value is 0, then...... */
{
coach1=coach1+1; /* .....coach1 will be incremented once instead of twice
since........ */
EEPROM.write(8,coach1);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
receive=receive*0;
EEPROM.write(13,receive);
r==0;
EEPROM.write(12,r);
Check==0;
EEPROM.write(4,Check);
}
else if(digitalRead(LSRRCVE1)==1&&coach1>12)
{
Tno=coach1+1;
EEPROM.write(9,Tno);
receive=receive*0;
EEPROM.write(13,receive);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
r==0;
EEPROM.write(12,r);
Check==0;
EEPROM.write(4,Check);
}
else if(digitalRead(LSRRCVE1)==1&&coach1>12&&receive==0)
{
Tno=coach1;
EEPROM.write(9,Tno);
receive=receive*0;
EEPROM.write(13,receive);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
r==0;
EEPROM.write(12,r);
Check==0;
EEPROM.write(4,Check);
}
else /* ........ the receiver value would not have incremented due to power
interruption at transmitter side that would have happened while Check was 0 at
both sides. This is the reason why the receiver uses “wait" value so that it waits
for sender to send light and then continues. */
{
if(receive==0) /* It sends light twice to indicate that receiver needs correct
value. */
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
Check==0;
EEPROM.write(4,Check);
}
else
{
coach1=coach1+1;
EEPROM.write(8,coach1);
receive=receive-1;
EEPROM.write(13,receive);
}
}
}
else /* After three times transmission to sender, if it receives light two times
instead of three or four, then receiver will understand that Check value at sender
side is still zero and sends light twice.*/
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
}
}
}
}
}
else
if(Step==1&&coach1>=0&&P2>20&&Fix==1&&(Check==0||Check==1)&&r==0&&
t!=1) /* Transmission takes place if coach1 is not zero. */
{
t==2; /* "t=2" means Transmitter 2 */
EEPROM.write(15,t);
Fix==1;
EEPROM.write(11,Fix);
while(send<=coach1&&(digitalRead(LSRRCVE2)==1||digitalRead(LSRRCVE2)==0)
&&S==0&&Check==0)
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50); /* Laser Transmitter sends light to the receiver until "send" variable
becomes equal to "coach1". */
if(digitalRead(LSRRCVE2)==1) /* "send" variable will be incremented only after
receiving a confirmation Laser signal from the receiver. */
{
send++;
EEPROM.write(16,send);
if(send==coach1) /* If send is equal to coach1, then Transmitter sends Laser
light to the receiver twice so that Check value becomes 1 at the receiver side. */
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
Error==0;
EEPROM.write(17,Error);
time=time*0;
EEPROM.write(18,time);
if(digitalRead(LSRRCVE2)==1) /* Then "Check" value becomes 1 at
Transmitter side if it receives Laser light twice from the receiver. */
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
else /* But when the Transmitter does not receive any signal even after sending
Laser light, then......... */
{
time==0;
EEPROM.write(18,time);
while(time<1000) /* ..........Condition is checked until time value reaches 1000.
*/
{
if(digitalRead(LSRRCVE2)==1) /* If receiver sends laser light indicating
ACTIVE mode, then....... */
{
loop(); /* ........moves to this function to reduce time lapse between Sender and
Receiver due to power interruption. */
break;
} /* This is the reason for using "Fix" variable as 1 since it skips the P1 & P2
measurement. */
else
{
time++; /* If Laser light is still not received by transmitter, "time" is
incremented. */
EEPROM.write(18,time);
}
}
if(time==1000&&lock<2&&coach1>12) /* If time value becomes 1000, coach1
value is greater than 13, then........ */
{
tno1=coach1; /* ......... coach1 value is given to tno1. */
EEPROM.write(7,tno1);
/* Depending upon P1 and P2 values, coach1 will be one or zero and....... */
if(P1>20&&P2<20)
{
coach1==1;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==3;
EEPROM.write(6,Step);
lock==2;
EEPROM.write(5,lock);
Error==1; /* ......Error becomes 1 indicating Train number
transmission error. And it goes to Step 3 since the compartment received both
Train & Coach number.*/
EEPROM.write(17,Error);
}
else if(P1<20&&(P2<20||P2>20))
{
coach1==0;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==2; /* Step 2 so that it can receive Station code and Platform
number. */
EEPROM.write(6,Step);
lock==1;
EEPROM.write(5,lock);
t==0;
EEPROM.write(15,t);
Error==1;
EEPROM.write(17,Error);
}
else
{
}
break;
}
else if(time==1000&&lock<2&&coach1<13&&tno1!=0) /* If coach1 value is
lesser than 13, then........... */
{
Step==3;
EEPROM.write(6,Step);
Error==2; /* ........Error becomes 2 indicating Coach number
transmission error. */
EEPROM.write(17,Error);
break;
}
else
{
}
}
}
while((digitalRead(LSRRCVE2)==0||digitalRead(LSRRCVE2)==1)&&S>0&&Check
==0) /* S is equal to “send" which happens due to twice light detection from
receiver indicating that receiver had not received the value completely. */
{
digitalWrite(LSRSND2,HIGH);
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
S--;
EEPROM.write(19,S);
if(S==0)
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
else
{
time==0;
EEPROM.write(18,time);
while(time<1000)
{
if(digitalRead(LSRRCVE2)==1)
{
loop();
break;
}
else
{
time++;
EEPROM.write(18,time);
}
}
if(time==1000&&lock==0&&coach1>12)
{
tno1=coach1;
EEPROM.write(7,tno1);
if(P1<10&&P2>10)
{
coach1==1;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==3;
EEPROM.write(6,Step);
lock==2;
EEPROM.write(5,lock);
Error==1;
EEPROM.write(17,Error);
}
else if(P1<10&&(P2<10||P2>10))
{
coach1==0;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==2;
EEPROM.write(6,Step);
lock==1;
EEPROM.write(5,lock);
t==0;
EEPROM.write(15,t);
Error==1;
EEPROM.write(17,Error);
}
else
{
}
break;
}
else if(time==1000&&lock==1&&coach1<12&&tno1!=0)
{
Step==3;
EEPROM.write(6,Step);
Error==2;
EEPROM.write(17,Error);
break;
}
else
{
}
}
}
while(Check==0&&send==coach1) /* Due to power interruption, transmitter
would not have received Laser light twice. So Check value remains zero. */
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1) /* In this situation, it sends Laser light for two
times instead of 3 or 4 after receiving laser light three times from the receiver
whose “Check" value is 1. */
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
else
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
else
{
time==0;
EEPROM.write(18,time);
while(time<1000)
{
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
else
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
else
{
time++;
EEPROM.write(18,time);
if(time==1000&&lock==0&&coach1>12)
{
tno1=coach1;
EEPROM.write(7,tno1);
if(P1<10&&P2>10)
{
coach1==1;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==3;
EEPROM.write(6,Step);
lock==2;
EEPROM.write(5,lock);
Error==1;
EEPROM.write(17,Error);
}
else if(P1<10&&(P2<10||P2>10))
{
coach1==0;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==2;
EEPROM.write(6,Step);
lock==1;
EEPROM.write(5,lock);
t==0;
EEPROM.write(15,t);
Error==1;
EEPROM.write(17,Error);
}
else
{
}
break;
}
else if(time==1000&&lock==1&&coach1<12&&tno1!=0)
{
Step==3;
EEPROM.write(6,Step);
Error==2;
EEPROM.write(17,Error);
break;
}
else
{
}
}
}
}
}
while(Check==1&&send>0) /* Condition after transmission where Check==1
and send value is greater than 0. */
{
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1) /* If Transmitter receives Laser three times
from receiver, then...............*/
{
send=send-1; /* ..........send value is decremented. */
EEPROM.write(16,send);
if(send==0) /* If "send" value becomes 0 after decrement, then Transmitter
sends Laser light four times and makes "Check" value 0 after receiving light from
receiver for one time. */
{
t==0;
EEPROM.write(15,t);
if(coach1<13)
{
Step==3;
EEPROM.write(6,Step);
}
else
{
tno1=coach1;
EEPROM.write(7,tno1);
}
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
Check==0;
EEPROM.write(4,Check);
/* If coach1 value is greater than 12, then that value will be tno1 value and
goes to Step 2 to receive station code and platform number. If less, then it goes to
step 3....... */
if(lock<2&&coach1>12)
{
lock==1; /* lock value 1 will fix this train number until P1 and P2 values
becomes lower. */
EEPROM.write(5,lock);
Step==0;
EEPROM.write(6,Step);
}
else if(lock<2&&coach1<13&&tno1!=0)
{
lock==2; /* lock value 2 will fix coach number. But after departure from
station, station code and platform number changes by means of light sensor and
lock becomes 1 so that coach value is received and transmitted again. */
EEPROM.write(5,lock);
}
else
{
}
Fix==0; /* And Fix value becomes zero. */
EEPROM.write(11,Fix);
}
}
else /* If "send" variable is not zero after decrement, then it sends Laser light to
the receiver for three times so that receive value at receiver side decrements. */
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE2)==1&&S==0)
{
if(digitalRead(LSRRCVE2)==1&&S==0) /* This condition satisfies when the
receiver sends light twice indicating that it didn't receive the value from
transmitter completely. */
{
S=send*1; /* The decremented "send" variable is taken as "S" variable...... */
EEPROM.write(19,S);
Check==0; /* ........and Check becomes zero to transmit. */
EEPROM.write(4,Check);
}
}
}
Error==0; /* Error value becomes 0 from 1 if process continues after
power interruption. */
EEPROM.write(17,Error);
time=time*0;
EEPROM.write(18,time);
}
}
else /* This condition is same like previous condition such as receive is zero
due to improper acquirement. */
{
if(send==0) /* If “send" value is zero then four times transmission. Eventhough
the Check value at receiver side is zero, the receiver will have Laser
receiving condition loop for four times as shown in the loop after Laser
transmission by receiver indicating ACTIVE mode. */
{
t==0;
EEPROM.write(15,t);
if(coach1<13)
{
Step==3;
EEPROM.write(6,Step);
}
else
{
tno1=coach1;
EEPROM.write(7,tno1);
}
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
Check==0;
EEPROM.write(4,Check);
if(lock<2&&coach1>12)
{
lock==1;
EEPROM.write(5,lock);
Step==0;
EEPROM.write(6,Step);
}
else if(lock<2&&coach1<13&&tno1!=0)
{
lock==2;
EEPROM.write(5,lock);
}
else
{
}
Fix==0;
EEPROM.write(11,Fix);
}
}
else
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
S=(send*1)-1;
EEPROM.write(19,S);
Check==0;
EEPROM.write(4,Check);
}
}
}
}
else /* If no response from transmitter for three times, then time and Error are
varied as usual. */
{
time==0;
EEPROM.write(18,time);
while(time<1000)
{
if(digitalRead(LSRRCVE2)==1)
{
loop();
break;
}
else
{
time++;
EEPROM.write(18,time);
}
}
if(time==1000&&lock==0&&coach1>12)
{
tno1=coach1;
EEPROM.write(7,tno1);
if(P1<10&&P2>10)
{
coach1==1;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==3;
EEPROM.write(6,Step);
lock==2;
EEPROM.write(5,lock);
Error==1;
EEPROM.write(17,Error);
}
else if(P1<10&&(P2<10||P2>10))
{
coach1==0;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==2;
EEPROM.write(6,Step);
lock==1;
EEPROM.write(5,lock);
t==0;
EEPROM.write(15,t);
Error==1;
EEPROM.write(17,Error);
}
else
{
}
break;
}
else if(time==1000&&lock==1&&coach1<12&&tno1!=0)
{
Step==3;
EEPROM.write(6,Step);
Error==2;
EEPROM.write(17,Error);
break;
}
else
{
}
}
}
}
/* The next two else if is used to receive from 12th Compartment and send to
next compartment. This can be used when there is a coach repair in between
which becomes unable to receive the train number from the 1st compartment. */
else
if(Step==1&&P2>20&&(Fix==0||Fix==1)&&(Check==1||Check==0)&&(coach1==0
||t==0)&&r!=1)
{
Fix==1;
EEPROM.write(11,Fix);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
while(Check==0)
{
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1&&coach1<13)
{
coach1=coach1+2;
EEPROM.write(8,coach1);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
receive=receive*0;
EEPROM.write(13,receive);
if(digitalRead(LSRRCVE1)==1)
{
r==1;
EEPROM.write(12,r);
coach=coach1;
EEPROM.write(10,coach);
}
else
{
r==0;
EEPROM.write(12,r);
}
Check==0;
EEPROM.write(4,Check);
}
else if(digitalRead(LSRRCVE2)==1&&coach1<13&&receive==0)
{
coach1=coach1+1;
EEPROM.write(8,coach1);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
receive=receive*0;
EEPROM.write(13,receive);
if(digitalRead(LSRRCVE1)==1)
{
r==1;
EEPROM.write(12,r);
coach=coach1;
EEPROM.write(10,coach);
}
else
{
r==0;
EEPROM.write(12,r);
}
Check==0;
EEPROM.write(4,Check);
}
else if(digitalRead(LSRRCVE2)==1&&coach1>12)
{
Tno=coach1+1;
EEPROM.write(9,Tno);
receive=receive*0;
EEPROM.write(13,receive);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
if(digitalRead(LSRRCVE1)==1)
{
r==1;
EEPROM.write(12,r);
coach1==0;
EEPROM.write(8,coach1);
}
else if(digitalRead(LSRRCVE2)==1&&coach1>12&&receive==0)
{
Tno==coach1;
EEPROM.write(9,Tno);
receive=receive*0;
EEPROM.write(13,receive);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
if(digitalRead(LSRRCVE1)==1)
{
r==1;
EEPROM.write(12,r);
coach1==0;
EEPROM.write(8,coach1);
}
else
{
}
}
else
{
Check==1;
EEPROM.write(4,Check);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
}
}
else
{
r==2;
EEPROM.write(12,r);
receive=receive+1;
EEPROM.write(13,receive);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
Check==1;
EEPROM.write(4,Check);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
}
}
}
}
else
{
while(wait<1000)
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
Check==1;
EEPROM.write(4,Check);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
}
else
{
loop();
break;
}
}
else
{
if(wait=1000)
{
wait==0;
EEPROM.write(14,wait);
}
else
{
wait++;
EEPROM.write(14,wait);
}
}
}
}
}
while(digitalRead(LSRRCVE2)==0&&Check==1&&receive>=0)
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1)
{
delay(50);
if(digitalRead(LSRRCVE2)==1&&coach1<13)
{
coach1=coach1+2;
EEPROM.write(8,coach1);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
receive=receive*0;
EEPROM.write(13,receive);
if(digitalRead(LSRRCVE1)==1) /* . Consider 7th Coach receiver for instance.
After Confirming the value received from 8th Coach correct when it detects Laser
light from 6th coach, then........*/
{
r==1; /* ........ "r" becomes 1 so that it can receive from 6th coach
using Laser receiver 1. */
EEPROM.write(12,r);
coach=coach1;
EEPROM.write(10,coach);
}
else
{
r==0;
EEPROM.write(12,r);
}
Check==0;
EEPROM.write(4,Check);
}
else if(digitalRead(LSRRCVE2)==1&&coach1<13&&receive==0)
{
coach1=coach1+1;
EEPROM.write(8,coach1);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
receive=receive*0;
EEPROM.write(13,receive);
if(digitalRead(LSRRCVE1)==1)
{
r==1;
EEPROM.write(12,r);
coach=coach1;
EEPROM.write(10,coach);
}
else
{
r==0;
EEPROM.write(12,r);
}
Check==0;
EEPROM.write(4,Check);
}
else if(digitalRead(LSRRCVE2)==1&&coach1>12)
{
Tno=coach1+1;
EEPROM.write(9,Tno);
receive=receive*0;
EEPROM.write(13,receive);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
if(digitalRead(LSRRCVE1)==1)
{
r==1;
EEPROM.write(12,r);
coach1==0;
EEPROM.write(8,coach1);
}
else
{
r==0;
EEPROM.write(12,r);
}
Check==0;
EEPROM.write(4,Check);
}
else if(digitalRead(LSRRCVE2)==1&&coach1>12&&receive==0)
{
Tno==coach1;
EEPROM.write(9,Tno);
receive=receive*0;
EEPROM.write(13,receive);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
if(digitalRead(LSRRCVE1)==1)
{
r==1;
EEPROM.write(12,r);
coach1==0;
EEPROM.write(8,coach1);
}
else
{
r==0;
EEPROM.write(12,r);
}
Check==0;
EEPROM.write(4,Check);
}
else
{
if(receive==0)
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
Check==0;
EEPROM.write(4,Check);
}
else
{
coach1=coach1+1;
EEPROM.write(8,coach1);
receive=receive-1;
EEPROM.write(13,receive);
}
}
}
else
{
Check==1;
EEPROM.write(4,Check);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
}
}
}
}
}
else if(Step==1&&coach1>=0&&P1>20&&(Check==0||Check==1)&&r==0&&t!=2)
{
t==1;
EEPROM.write(15,t);
Fix==1;
EEPROM.write(11,Fix);
while(send<=coach1&&(digitalRead(LSRRCVE1)==0||digitalRead(LSRRCVE1)==1)
&&S==0&&Check==0)
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
if(digitalRead(LSRRCVE1)==1)
{
if(digitalRead(LSRRCVE1)==1)
{
send++;
EEPROM.write(16,send);
if(send==coach1)
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
Error==0;
EEPROM.write(17,Error);
time=time*0;
EEPROM.write(18,time);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
}
else
{
time==0;
EEPROM.write(18,time);
while(time<1000)
{
if(digitalRead(LSRRCVE1)==1)
{
loop();
break;
}
else
{
time++;
EEPROM.write(18,time);
}
}
if(time==1000&&lock==0&&coach1>12)
{
tno1=coach1;
EEPROM.write(7,tno1);
if(P1<10&&P2>10)
{
coach1==1;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==3;
EEPROM.write(6,Step);
lock==2;
EEPROM.write(5,lock);
}
else if(P1<10&&(P2<10||P2>10))
{
coach1==0;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==2;
EEPROM.write(6,Step);
lock==1;
EEPROM.write(5,lock);
t==0;
EEPROM.write(15,t);
}
else
{
}
}
else if(time==1000&&lock==1&&coach1<12&&tno1!=0)
{
Step==3;
EEPROM.write(6,Step);
}
else
{
}
}
}
while((digitalRead(LSRRCVE1)==0||digitalRead(LSRRCVE1)==1)&&S>0&&Check
==0)
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
S--;
EEPROM.write(19,S);
if(S==0)
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
else
{
time==0;
EEPROM.write(18,time);
while(time<1000)
{
if(digitalRead(LSRRCVE1)==1)
{
loop();
break;
}
else
{
time++;
EEPROM.write(18,time);
}
}
if(time==1000&&lock==0&&coach1>12)
{
tno1=coach1;
EEPROM.write(7,tno1);
if(P1<10&&P2>10)
{
coach1==1;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==3;
EEPROM.write(6,Step);
lock==2;
EEPROM.write(5,lock);
}
else if(P1<10&&(P2<10||P2>10))
{
coach1==0;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==2;
EEPROM.write(6,Step);
lock==1;
EEPROM.write(5,lock);
t==0;
EEPROM.write(15,t);
}
else
{
}
}
else if(time==1000&&lock==1&&coach1<12&&tno1!=0)
{
Step==3;
EEPROM.write(6,Step);
}
else
{
}
}
}
}
while(Check==0&&send==coach1)
{
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
Error==0;
EEPROM.write(17,Error);
time=time*0;
EEPROM.write(18,time);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
else
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
Error==0;
EEPROM.write(17,Error);
time=time*0;
EEPROM.write(18,time);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
else
{
time==0;
EEPROM.write(18,time);
while(time<1000)
{
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
Error==0;
EEPROM.write(17,Error);
time=time*0;
EEPROM.write(18,time);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
else
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
Error==0;
EEPROM.write(17,Error);
time=time*0;
EEPROM.write(18,time);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
Check==1;
EEPROM.write(4,Check);
}
}
}
}
else
{
time++;
EEPROM.write(18,time);
}
}
if(time==1000&&lock==0&&coach1>12)
{
tno1=coach1;
EEPROM.write(7,tno1);
if(P1<10&&P2>10)
{
coach1==1;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==3;
EEPROM.write(6,Step);
lock==2;
EEPROM.write(5,lock);
}
else if(P1<10&&(P2<10||P2>10))
{
coach1==0;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==2;
EEPROM.write(6,Step);
lock==1;
EEPROM.write(5,lock);
t==0;
EEPROM.write(15,t);
}
else
{
}
}
else if(time==1000&&lock==1&&coach1<12&&tno1!=0)
{
Step==3;
EEPROM.write(6,Step);
}
else
{
}
}
}
}
while(Check==1&&send>0)
{
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
send=send-1;
EEPROM.write(16,send);
if(send==0)
{
t==0;
EEPROM.write(15,t);
if(coach1<13)
{
Step==3;
EEPROM.write(6,Step);
}
else
{
tno1=coach1;
EEPROM.write(7,tno1);
}
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
if(digitalRead(LSRRCVE1)==1)
{
Check==0;
EEPROM.write(4,Check);
if(lock<2&&coach1>12)
{
lock==1;
EEPROM.write(5,lock);
Step==0;
EEPROM.write(6,Step);
}
else if(lock<2&&coach1<13)
{
lock==2;
EEPROM.write(5,lock);
}
else
{
}
Fix==0;
EEPROM.write(11,Fix);
}
}
else
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
if(digitalRead(LSRRCVE2)==1&&S==0)
{
if(digitalRead(LSRRCVE2)==1&&S==0)
{
S=send*1;
EEPROM.write(19,S);
Check==0;
EEPROM.write(4,Check);
}
}
}
Error==0;
EEPROM.write(17,Error);
time=time*0;
EEPROM.write(18,time);
}
}
else
{
if(send==0)
{
t==0;
EEPROM.write(15,t);
if(coach1<13)
{
Step==3;
EEPROM.write(6,Step);
}
else
{
tno1=coach1;
EEPROM.write(7,tno1);
}
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
if(digitalRead(LSRRCVE1)==1)
{
Check==0;
EEPROM.write(4,Check);
if(lock<2&&coach1>12)
{
lock==1;
EEPROM.write(5,lock);
Step==0;
EEPROM.write(6,Step);
}
else if(lock<2&&coach1<13)
{
lock==2;
EEPROM.write(5,lock);
}
else
{
}
Fix==0;
EEPROM.write(11,Fix);
}
}
else
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
if(digitalRead(LSRRCVE1)==1)
{
S=(send*1)-1;
EEPROM.write(19,S);
Check==0;
EEPROM.write(4,Check);
}
}
}
}
else
{
time==0;
EEPROM.write(18,time);
while(time<1000)
{
if(digitalRead(LSRRCVE1)==1)
{
loop();
break;
}
else
{
time++;
EEPROM.write(18,time);
}
}
if(time==1000&&lock==0&&coach1>12)
{
tno1=coach1;
EEPROM.write(7,tno1);
if(P1<10&&P2>10)
{
coach1==1;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==3;
EEPROM.write(6,Step);
lock==2;
EEPROM.write(5,lock);
}
else if(P1<10&&(P2<10||P2>10))
{
coach1==0;
EEPROM.write(8,coach1);
coach==coach1;
EEPROM.write(10,coach);
Step==2;
EEPROM.write(6,Step);
lock==1;
EEPROM.write(5,lock);
t==0;
EEPROM.write(15,t);
}
else
{
}
}
else if(time==1000&&lock==1&&coach1<12&&tno1!=0)
{
Step==3;
EEPROM.write(6,Step);
}
else
{
}
}
}
}
else if(Step==1&&(t==0||P1<20||P2<20)&&Check==1)
{
Check==0;
EEPROM.write(4,Check);
Fix==0;
EEPROM.write(11,Fix);
if(lock<2&&coach1>12)
{
tno1=coach1;
EEPROM.write(7,tno1);
Step==2;
EEPROM.write(6,Step);
}
else
{
Step==3;
EEPROM.write(6,Step);
}
}
else if(Step==2&&tno1!=0&&Fix==1)
{
delay(10000);
if(TD<10) /* When Light detector placed at bottom of the train compartment has
value lesser than 10 indicating Lesser light intensity, then the following if-elseifelseif-
else containing different station codes for different light intensities are
followed. */
{
if(750<TD<775)
{
tno==tno1;
EEPROM.write(20,tno);
i==1;
EEPROM.write(21,i);
}
else if(775<TD<800)
{
tno==tno1+1;
EEPROM.write(20,tno);
i==1;
EEPROM.write(21,i);
}
else if(800<TD<=805)
{
i==2;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(805<TD<=810)
{
i==2;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(810<TD<=815)
{
i==3;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(815<TD<=820)
{
i==3;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(820<TD<=825)
{
i==4;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(825<TD<=830)
{
i==4;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(830<TD<=835)
{
i==5;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(835<TD<=840)
{
i==5;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(840<TD<=845)
{
i==6;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(845<TD<=850)
{
i==6;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(850<TD<=855)
{
i==7;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(855<TD<=860)
{
i==7;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(860<TD<=865)
{
i==8;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(865<TD<=870)
{
i==8;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(870<TD<=875)
{
i==9;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(875<TD<=880)
{
i==9;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(880<TD<=885)
{
i==10;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(885<TD<=890)
{
i==10;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(890<TD<=895)
{
i==11;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(895<TD<=900)
{
i==11;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(900<TD<=905)
{
i==12;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(905<TD<=910)
{
i==12;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(910<TD<=915)
{
i==13;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(915<TD<=920)
{
i==13;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(920<TD<=925)
{
i==14;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(925<TD<=930)
{
i==14;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(930<TD<=935)
{
i==15;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(935<TD<=940)
{
i==15;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(940<TD<=945)
{
i==16;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(945<TD<=950)
{
i==16;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(950<TD<=955)
{
i==17;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(955<TD<=960)
{
i==17;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(960<TD<=965)
{
i==18;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(965<TD<=970)
{
i==18;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(970<TD<=975)
{
i==19;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(975<TD<=980)
{
i==19;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(980<TD<=985)
{
i==20;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(985<TD<=990)
{
i==20;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(990<TD<=995)
{
i==21;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(995<TD<=1000)
{
i==21;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(1000<TD<=1005)
{
i==22;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(1005<TD<=1010)
{
i==22;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(1010<TD<=1015)
{
i==23;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(1015<TD<=1020)
{
i==23;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(1020<TD<=1025)
{
i==24;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(1025<TD<=1030)
{
i==24;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else if(1030<TD<=1035)
{
i==25;
EEPROM.write(21,i);
j==0;
EEPROM.write(22,j);
}
else if(1035<TD<=1040)
{
i==25;
EEPROM.write(21,i);
j==1;
EEPROM.write(22,j);
}
else
{
}
if(2<=i<=7) /* Then tno is given tno1 or tno2 value based on station code.
Because........... */
{
tno==tno1;
EEPROM.write(20,tno);
}
else if(8<=i<=13)
{
tno==tno1+1;
EEPROM.write(20,tno);
}
else
{
}
}
else /* .......... after 3.5 seconds delay if no light detection happens due to power
interruption at station or train, then the train changes the station code by itself
based on tno value thus reduces delay in transmission to the upcoming station. */
{
if((2<=i<=7)&&(tno%2==1)) /* Station code from 2 to 7 is used for Forward
Journey. */
{
if(i==7)
{
i==2;
EEPROM.write(21,i);
}
else
{
i++;
EEPROM.write(21,i);
}
}
else if((8<=i<=13)&&(tno%2==0)) /* Station codes 8 to 13 for Return Journey*/
{
if(i==13)
{
i==8;
EEPROM.write(21,i);
}
else
{
i++;
EEPROM.write(21,i);
}
}
else
{
}
}
flag=flag*0;
EEPROM.write(23,flag);
time=time*0;
EEPROM.write(18,time);
TD=analogRead(sensorpin);
P1=analogRead(sensorpin);
P2=analogRead(sensorpin);
if(lock==1&&Error==0) /* If train number is received and transmitted, then lock
becomes 1 so that after station code acquirement, it moves to Step 1. */
{
Step==1;
EEPROM.write(6,Step);
coach1==coach;
EEPROM.write(8,coach1);
} /* If Error is 1, then Train number Tno is given to coach1 variable. If 2, then
coach number either 1 or 0 is given to coach1 variable. Coach number is 1 if it is a
1st compartment and 0 if it is compartments in-between 1st and 12th. */
else if(((lock==1||lock==2)&&Error==1)&&(P1<20&&P2>20))
{
Step==1;
EEPROM.write(6,Step);
lock==0;
EEPROM.write(5,lock);
coach1==Tno;
EEPROM.write(8,coach1);
}
else if(((lock==1||lock==2)&&Error==2)&&(P1<20&&P2>20))
{
Step==1;
EEPROM.write(6,Step);
lock==1;
EEPROM.write(5,lock);
coach1==coach;
EEPROM.write(8,coach1);
}
else if(((lock==1||lock==2)&&Error==1)&&(P1>20&&(P2>20||P2<20)))
{
Step==1;
EEPROM.write(6,Step);
lock==0;
EEPROM.write(5,lock);
coach1==Tno;
EEPROM.write(8,coach1);
}
else if(((lock==1||lock==2)&&Error==2)&&(P1>20&&(P2>20||P2<20)))
{
Step==1;
EEPROM.write(6,Step);
lock==1;
EEPROM.write(5,lock);
coach1==0;
EEPROM.write(8,coach1);
}
else if(lock==2&&Error==0)
{
Step==3;
EEPROM.write(6,Step);
}
else
{
}
}
else if(Step==3) /* At Step 3, coach1 as 1 will become 12 for coach2, 2 will become
11 and goes on. tno1 will be added by 1 to give tno2. */
{
coach1==coach;
EEPROM.write(8,coach1);
if(coach1==1)
{
coach2==12;
EEPROM.write(24,coach2);
}
else if(coach1==2)
{
coach2==11;
EEPROM.write(24,coach2);
}
else if(coach1==3)
{
coach2==10;
EEPROM.write(24,coach2);
}
else if(coach1==4)
{
coach2==9;
EEPROM.write(24,coach2);
}
else if(coach1==5)
{
coach2==8;
EEPROM.write(24,coach2);
}
else if(coach1==6)
{
coach2==7;
EEPROM.write(24,coach2);
}
else if(coach1==7)
{
coach2==6;
EEPROM.write(24,coach2);
}
else if(coach1==8)
{
coach2==5;
EEPROM.write(24,coach2);
}
else if(coach1==9)
{
coach2==4;
EEPROM.write(24,coach2);
}
else if(coach1==10)
{
coach2==3;
EEPROM.write(24,coach2);
}
else if(coach1==11)
{
coach2==2;
EEPROM.write(24,coach2);
}
else if(coach1==12)
{
coach2==1;
EEPROM.write(24,coach2);
}
else
{
}
tno2=tno1+1;
EEPROM.write(25,tno2);
lock==2;
EEPROM.write(5,lock);
Step==4;
EEPROM.write(6,Step);
}
else if(Step==4)
{
k==30;
while(k<42) /* 31 to 42 are Arduino pin numbers. They are used for iteration
process to send signal one by one to Arduinos at exits. */
{
digitalWrite(k+1,HIGH); /* After sending signal to 1st Arduino,........ */
c[(k-30)]=Wire.read(); /* ......... that Arduino sends count details that it had
collected by PIR motion sensor........... */
if(digitalRead(CNTRCVD)==1) /* ...........and sends Acknowledgement so
that......... */
{
digitalWrite(k+1,LOW); /* ........signal from Arduino at centre will switch OFF. */
k++;
}
else if(digitalRead(CNTRCVD)==1&&k==41)
{
digitalWrite(k+1,LOW);
k++;
counter=c[0]+ c[1]+ c[2]+ c[3]+ c[4]+c[5]+ c[6]+ c[7]+ c[8]+ c[9]+ c[10]+ c[11]; /* This loop follows until all pins are used and finally the count details acquired from each exits are added and displayed. */
EEPROM.write(26,counter);
int count;
if(0<=counter<=25)
{
count=(counter*10)+1;
}
else if(26<=counter<=130)
{
count=(counter*10)+2;
}
else if(131<=counter<=145)
{
count=(counter*10)+3;
}
else if(counter>=146)
{
count=(counter*10)+4;
}
else
{
}
sevseg.setNumber(count,1);
sevseg.refreshDisplay();
}
else
{
}
}
if(P1<20&&P2<20) /* To check whether compartment is detached. */
{
lock==0;
EEPROM.write(5,lock);
Step==1;
EEPROM.write(6,Step);
tno1==0;
EEPROM.write(7,tno1);
coach1==0;
EEPROM.write(8,coach1);
}
if((730<TD<750||flag==1)||(DA==1||time==250)) /* When Light detector fixed
at train's bottom detects intensity at the value between 750 and 750, then flag
becomes 1 from 0, ......*/
{
if(flag==0)
{
flag=flag+1;
EEPROM.write(23,flag);
digitalWrite(SETPIN,LOW);
HC12.print("AT+B115200"); /* .....Baud rate of 115200 decreases transmission
distance,..... */
digitalWrite(SETPIN,HIGH);
}
else
{
digitalWrite(SETPIN,LOW);
HC12.print("AT+B9600"); /* .....Baud rate of 115200 decreases transmission
distance,..... */
digitalWrite(SETPIN,HIGH);
}
if((02<=stno<=07)&&(0<coach1<13)&&Error==0&&X!=0)
{
details=((tno1*100000000)+(stno[i]*1000000)+(pltfmno[j]*100000)+((coach1*1000)+counter)); /* .......the train number, station code, platform number, coach number &
counter are joined together, ....... */
EEPROM.write(27,details);
d=(tno1*100000000)+(stno[i]*1000000)+(pltfmno[j]*100000)+(coach1*1000);
EEPROM.write(28,d);
}
else if((8<=stno<=13)&&(0<coach2<13)&&Error==0&&X!=0)
{
details=((tno2*100000000)+(stno[i]*1000000)+(pltfmno[j]*100000)+((coach2*1000)+counter));
EEPROM.write(27,details);
d=(tno2*100000000)+(stno[i]*1000000)+(pltfmno[j]*100000)+(coach2*1000);
EEPROM.write(28,d);
}
else if((02<=stno<=07)&&(0<coach1<13)&&Error==1&&X!=0)
{
details=((tno1*100000000)+(stno[i]*1000000)+((pltfmno[j]+2)*100000)+((coach1*1000)
+counter));
EEPROM.write(27,details);
d=(tno1*100000000)+(stno[i]*1000000)+((pltfmno[j]+2)*100000)+(coach1*1000);
EEPROM.write(28,d);
}
else if((8<=stno<=13)&&(0<coach2<13)&&Error==1&&X!=0)
{
details=((tno2*100000000)+(stno[i]*1000000)+((pltfmno[j]+2)*100000)+((coach2*1000)
+counter));
EEPROM.write(27,details);
d=(tno2*100000000)+(stno[i]*1000000)+((pltfmno[j]+2)*100000)+(coach2*1000);
EEPROM.write(28,d);
}
else if((14<=stno<=25)&&(0<coach1<13)&&Error==0&&(tno%2==1)&&X!=0)
{
details=((tno1*100000000)+(stno[i]*1000000)+(pltfmno[j]*100000)+((coach1*1000)+counter));
EEPROM.write(27,details);
d=(tno1*100000000)+(stno[i]*1000000)+(pltfmno[j]*100000)+(coach1*1000);
EEPROM.write(28,d);
}
else if((14<=stno<=25)&&(0<coach2<13)&&Error==0&&(tno%2==0)&&X!=0)
{
details=((tno2*100000000)+(stno[i]*1000000)+(pltfmno[j]*100000)+((coach2*1000)+counter));
EEPROM.write(27,details);
d=(tno2*100000000)+(stno[i]*1000000)+(pltfmno[j]*100000)+(coach2*1000);
EEPROM.write(28,d);
}
else if((14<=stno<=25)&&(0<coach1<13)&&Error==1&&(tno%2==1)&&X!=0)
{
details=((tno1*100000000)+(stno[i]*1000000)+((pltfmno[j]+2)*100000)+((coach1*1000)
+counter));
EEPROM.write(27,details);
d=(tno1*100000000)+(stno[i]*1000000)+((pltfmno[j]+2)*100000)+(coach1*1000);
EEPROM.write(28,d);
}
else if((14<=stno<=25)&&(0<coach2<13)&&Error==1&&(tno%2==0)&&X!=0)
{
details=((tno2*100000000)+(stno[i]*1000000)+((pltfmno[j]+2)*100000)+((coach2*1000)
+counter));
EEPROM.write(27,details);
d=(tno2*100000000)+(stno[i]*1000000)+((pltfmno[j]+2)*100000)+(coach2*1000);
EEPROM.write(28,d);
}
else
{
}
HC12.write(details); /* ........ and sent to the upcoming station. If Error is 1, then
Platform number is incremented twice. tno1 and coach1 will be used if station
code is between 2 and 7 and tno2 and coach2 is used if between 8 and 13. If
between 14 and 25, tno takes tno1 value if light intensity is between 750 and 775
and tno2 value if between 775 and 800. "Tno" variable is fixed whereas "tno"
variable is varied if station with multiple platform arrives.*/
delay(2000);
if(HC12.available()==1) /* After 2 seconds delay, if train compartment receives
detail from station...... */
{
X=HC12.read();
EEPROM.write(3,X);
if(X!=d) /* ......then it checks whether the detail sent is wrong or not. If yes,
it is rectified. */
{
details=X+counter;
EEPROM.write(27,details);
d==X; /* d contains Train number, Station code, Platform number and Coach
number. */
EEPROM.write(28,d);
}
tno=d*(10^-8);
EEPROM.write(20,tno);
}
time++;
EEPROM.write(18,time);
}
else if((700<TD<730)||time==275) /* When train number crosses from TD2 to
TD1 before arriving at the station, Light source T2 placed near TD2 emits light
with light intensity between 700 and 730 and T1 is in OFF condition. */
{
DA==1; /* Due to light emission, DA becomes 1 indicating Departure
Arrival*/
EEPROM.write(1,DA);
time=time*0;
EEPROM.write(18,time);
}
else if(TD<700) /* If no light emission occurs, then time is incremented so that
Train sends details if time is 10 or sends Status if time is 15 and makes time value
0. */
{
while(time<=250&&TD<700)
{ /* If Laser receiver sends light, then transmitter sends light four times so that
Receiver can collect Train number or Station code. */
if(digitalRead(LSRRCVE1)==1&&t==0)
{
delay(50);
if(digitalRead(LSRRCVE1)==1&&t==0)
{
delay(50);
if(digitalRead(LSRRCVE1)==1&&t==0)
{
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
delay(50);
digitalWrite(LSRSND1,HIGH);
delay(50);
digitalWrite(LSRSND1,LOW);
time==250;
EEPROM.write(18,time);
}
}
}
else if(digitalRead(LSRRCVE2)==1&&t==0)
{
delay(50);
if(digitalRead(LSRRCVE1)==1&&t==0)
{
delay(50);
if(digitalRead(LSRRCVE1)==1&&t==0)
{
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
delay(50);
digitalWrite(LSRSND2,HIGH);
delay(50);
digitalWrite(LSRSND2,LOW);
time==250;
EEPROM.write(18,time);
}
}
}
else if(digitalRead(LSRRCVE1)==1&&Error==1&&t!=1) /* If receiver sends light
when "Error" is 1, then it goes to Step 1 for transmission*/
{
Step==1;
EEPROM.write(6,Step);
Fix==1;
EEPROM.write(11,Fix);
time==250;
EEPROM.write(18,time);
loop();
}
else if(digitalRead(LSRRCVE2)==1&&t!=2)
{
Step==1;
EEPROM.write(6,Step);
Fix==1;
EEPROM.write(11,Fix);
time==250;
EEPROM.write(18,time);
loop();
}
else
{
time++;
EEPROM.write(18,time);
}
}
}
else
{
}
if(DA==1&&coach1==1&&coach2==12) /* If DA is 1 and compartment is first or
last, then......... */
{
Status==1; /* ....... Status becomes 1. */
EEPROM.write(2,Status);
if(digitalRead(PIR)==0&&time==10&&Status==1)
{
Status==2; /* Status becomes 2 only when time becomes 10, because after
reaching TD2, it takes time of about 15 seconds to reach the platform completely.
10 seconds and remaining few seconds takes place during loop process of Step 4.
*/
EEPROM.write(2,Status);
if(X!=d) /* If Status value is wrong, then it rectifies and at next attempt...... */
{
d==X;
EEPROM.write(28,d);
Sts=X+1;
}
else
{
Sts=d+1;
}
EEPROM.write(29,Sts);
HC12.write(Sts); /* ...... it sends Sts adding "d" with 1 where 1 indicates Letter
"A" meaning arrival */
time++;
EEPROM.write(18,time);
delay(1000);
if(digitalRead(LSRRCVE)==1&&DA==1&&Status==1) /* This indicates Laser
light emittance from station for Confirmation of Train number if receives a wrong
station code. */
{
digitalWrite(TL1,HIGH);
digitalWrite(TL2,HIGH);
}
}
else if((digitalRead(PIR)==1||digitalRead(PIR)==0)&&Status==1)
{
time++;
EEPROM.write(18,time);
delay(1000);
}
else if(digitalRead(PIR)==1&&time==10&&Status==2) /* When train departs as
shown by PIR detection and Status value of 2, then........ */
{
DA==0;
EEPROM.write(1,DA);
Status==0;
EEPROM.write(2,Status);
Check==0;
EEPROM.write(4,Check);
Sts=d+4;
EEPROM.write(29,Sts);
HC12.write(Sts); /* .......... Sts value is sent to station with last digit as 4
indicating "D" meaning Departure. With this value the station makes Status 4 so
that Departed train erases when it goes over Light detectors.*/
X==0;
EEPROM.write(3,X);
Step==0;
EEPROM.write(6,Step);
Fix==0;
EEPROM.write(11,Fix);
digitalWrite(TL1,LOW);
digitalWrite(TL2,LOW);
}
else
{
}
}
else
{
}
}
}
