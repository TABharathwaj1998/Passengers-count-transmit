                                            /* Arduino program to count passengers in a Train compartment */
#include<EEPROM.h> /* EEPROM is used for permanent storage of variables which will prevent erasing of values when
the power is switched OFF. */
#include<Wire.h>
#define PIR1 22
#define PIR2 23
#define PIR3 24 /* PIR (Passive Infrared motion sensor) is used for counting the passengers. */
#define PIR6 25
#define PIR7 26
#define PIR8 27
#define PIR9 28
#define CNTACK 29
#define CNTSNT 3
extern int counter=0,c=0,*count=0,a=0,flag=0,e1=0,e2=0,e7=0,e8=0,*p=0,*q=0,*r=0,*s=0,eoe=0,Alerten=0,*ena=0,Alertex=0,*exa=0;
void upcount(int *p,int *q, int *r, int *s, int *count, int *ena);
void downcount(int *p,int *q,int *r, int *s, int *count, int *exa);
void nocount1(int *p,int *s,int *count,int *ena,int *exa);
void nocount2(int *q,int *r,int *count,int *ena,int *exa);
void compnx(int *r, int *s, int *p, int*q, int *count);
/* Five call by pointer functions described above are used to make the counting process with minimum errors and delays. */
void setup()
{
pinMode(PIR1,INPUT);
pinMode(PIR2,INPUT);
pinMode(PIR3,INPUT);
pinMode(PIR6,INPUT);
pinMode(PIR7,INPUT);
pinMode(PIR8,INPUT);
pinMode(PIR9,INPUT);
pinMode(CNTACK,INPUT);
pinMode(CNTSNT,OUTPUT);
Wire.begin();
*count=EEPROM.read(0);
*p=EEPROM.read(1);
*q=EEPROM.read(2);
*ena=EEPROM.read(3);
*r=EEPROM.read(4);
*s=EEPROM.read(5);
*exa=EEPROM.read(6);
Alerten=EEPROM.read(7);
counter=EEPROM.read(8);
e1=EEPROM.read(9);
e2=EEPROM.read(10);
Alertex=EEPROM.read(11);
e8=EEPROM.read(12);
e7=EEPROM.read(13);
}
/* If two passengers enters/exits at the same time but crosses PIR sensors at different timings, then the following user defined
functions upcount and downcount is used to count the second passenger immediately after the boarding/exiting done by the
previous passenger. */
void upcount(int *p,int *q,int *r,int *s,int *count,int *ena)
{
delay(650);
if((digitalRead(PIR8)==1&&(*p)==0)&&digitalRead(PIR1)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR8)==1&&(*p)==1)&&digitalRead(PIR1)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*p=(*p)*0;
EEPROM.write(1,*p);
}
else if((digitalRead(PIR1)==1&&(*p)==1)&&digitalRead(PIR8)==0)
{
*p=(*p)*0;
EEPROM.write(1,*p);
}
else if((digitalRead(PIR7)==1&&(*q)==0)&&digitalRead(PIR2)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR7)==1&&(*q)==1)&&digitalRead(PIR2)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*q=(*q)*0;
EEPROM.write(2,*q);
}
else if((digitalRead(PIR2)==1&&(*q)==1)&&digitalRead(PIR7)==0)
{
*q=(*q)*0;
EEPROM.write(2,*q);
}
else
{
}
if(digitalRead(PIR8)==0&&digitalRead(PIR7)==0)
{
*ena==0;
EEPROM.write(3,*ena);
}
else
{
*ena==1;
EEPROM.write(3,*ena);
}
}
void downcount(int *p,int *q, int *r,int *s,int *count,int *exa)
{
delay(650);
if((digitalRead(PIR1)==1&&(*r)==0)&&digitalRead(PIR8)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR1)==1&&(*r)==1)&&digitalRead(PIR8)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*r=(*r)*0;
EEPROM.write(4,*r);
}
else if((digitalRead(PIR8)==1&&(*r)==1)&&digitalRead(PIR1)==0)
{
*r=(*r)*0;
EEPROM.write(4,*r);
}
else if((digitalRead(PIR2)==1&&(*s)==0)&&digitalRead(PIR7)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR2)==1&&(*s)==1)&&digitalRead(PIR7)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*s=(*s)*0;
EEPROM.write(5,*s);
}
else if((digitalRead(PIR7)==1&&(*s)==1)&&digitalRead(PIR2)==0)
{
*s=(*s)*0;
EEPROM.write(5,*s);
}
else
{
}
if(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)
{
*exa==0;
EEPROM.write(6,*exa);
}
else
{
*exa==1;
EEPROM.write(6,*exa);
}
}
/* Formal parameters nocount1() and nocount2() are used to avoid count if entering and exiting takes place simultaneously. */
void nocount1(int *p,int *s,int *count,int *ena,int *exa)
{
if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
*count=(*count)+0;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
*count=(*count)+1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==1))
{
*count=(*count)+1;
EEPROM.write(0,*count);
*s==1;
EEPROM.write(5,*s);
delay(665);
if(digitalRead(PIR2)==1&&digitalRead(PIR7)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*s==0;
EEPROM.write(5,*s);
}
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
*count=(*count)-1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
*count=(*count)-1;
EEPROM.write(0,*count);
*p==1;
EEPROM.write(1,*p);
if(digitalRead(PIR8)==1&&digitalRead(PIR1)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*p==0;
EEPROM.write(1,*p);
}
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==1))
{
*p==1;
EEPROM.write(1,*p);
*s==1;
EEPROM.write(5,*s);
if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
*count=(*count)+0;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
*count=(*count)+1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==1))
{
*count=(*count)+1;
EEPROM.write(0,*count);
*s==1;
EEPROM.write(5,*s);
delay(665);
if(digitalRead(PIR2)==1&&digitalRead(PIR7)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*s==0;
EEPROM.write(5,*s);
}
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
*count=(*count)-1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
*count=(*count)-1;
EEPROM.write(0,*count);
*p==1;
EEPROM.write(1,*p);
if(digitalRead(PIR8)==1&&digitalRead(PIR1)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*p==0;
EEPROM.write(1,*p);
}
}
else
{
}
}
else
{
}
if(digitalRead(PIR8)==0&&digitalRead(PIR7)==0)
{
*ena==0;
EEPROM.write(5,*ena);
}
else
{
*ena==1;
EEPROM.write(5,*ena);
}
if(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)
{
*exa==0;
EEPROM.write(6,*exa);
}
else
{
*exa==1;
EEPROM.write(6,*exa);
}
}
void nocount2(int *q,int *r,int *count,int *ena,int *exa)
{
if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
*count=(*count)+0;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==1))
{
*count=(*count)+1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==1))
{
*count=(*count)+1;
EEPROM.write(0,*count);
*r==1;
EEPROM.write(4,*r);
if(digitalRead(PIR1)==1&&digitalRead(PIR8)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
}
}
else if((digitalRead(PIR7)==0&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
*count=(*count)-1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
*count=(*count)-1;
EEPROM.write(0,*count);
*q==1;
EEPROM.write(2,*q);
if(digitalRead(PIR7)==1&&digitalRead(PIR2)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*q==0;
EEPROM.write(2,*q);
}
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==1))
{
*r==1;
EEPROM.write(4,*r);
*q==1;
EEPROM.write(2,*q);
if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
*count=(*count)+0;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==1))
{
*count=(*count)+1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==1))
{
*count=(*count)+1;
EEPROM.write(0,*count);
*r==1;
EEPROM.write(4,*r);
if(digitalRead(PIR1)==1&&digitalRead(PIR8)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
}
}
else if((digitalRead(PIR7)==0&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
*count=(*count)-1;
EEPROM.write(0,*count);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
*count=(*count)-1;
EEPROM.write(0,*count);
*q==1;
EEPROM.write(2,*q);
if(digitalRead(PIR7)==1&&digitalRead(PIR2)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*q==0;
EEPROM.write(2,*q);
}
}
else
{
}
}
else
{
}
if(digitalRead(PIR8)==0&&digitalRead(PIR7)==0)
{
*ena==0;
EEPROM.write(3,*ena);
}
else
{
*ena==1;
EEPROM.write(3,*ena);
}
if(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)
{
*exa==0;
EEPROM.write(6,*exa);
}
else
{
*exa==1;
EEPROM.write(6,*exa);
}
}
void compnx(int *r, int *s, int *p, int*q, int *count) /* This function is called when the passenger stands below the PIR sensor for
the long time without entering or exiting. */
{
if(digitalRead(PIR8)==1&&((*p)==1)&&digitalRead(PIR1)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*p==0;
EEPROM.write(1,*p);
delay(665);
if(digitalRead(PIR7)==1&&((*q)==1)&&digitalRead(PIR2)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*q==0;
EEPROM.write(2,*q);
}
else if(digitalRead(PIR2)==1&&((*q)==1)&&digitalRead(PIR7)==0)
{
*q==0;
EEPROM.write(2,*q);
}
else
{
}
}
else if(digitalRead(PIR1)==1&&((*p)==1)&&digitalRead(PIR8)==0)
{
*p==0;
EEPROM.write(1,*p);
delay(665);
if(digitalRead(PIR7)==1&&((*q)==1)&&digitalRead(PIR2)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*q==0;
EEPROM.write(2,*q);
}
else if(digitalRead(PIR2)==1&&((*q)==1)&&digitalRead(PIR7)==0)
{
*q==0;
EEPROM.write(2,*q);
}
else
{
}
}
else if(digitalRead(PIR7)==1&&((*q)==1)&&digitalRead(PIR2)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*q==0;
EEPROM.write(2,*q);
delay(665);
if(digitalRead(PIR8)==1&&((*p)==1)&&digitalRead(PIR1)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*p==0;
EEPROM.write(1,*p);
}
else if(digitalRead(PIR1)==1&&((*p)==1)&&digitalRead(PIR8)==0)
{
*p==0;
EEPROM.write(1,*p);
}
else
{
}
}
else if(digitalRead(PIR2)==1&&((*q)==1)&&digitalRead(PIR7)==0)
{
*q==0;
EEPROM.write(2,*q);
delay(665);
if(digitalRead(PIR8)==1&&((*p)==1)&&digitalRead(PIR1)==0)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*p==0;
EEPROM.write(1,*p);
}
else if(digitalRead(PIR1)==1&&((*p)==1)&&digitalRead(PIR8)==0)
{
*p==0;
EEPROM.write(1,*p);
}
else
{
}
}
else
if(((digitalRead(PIR8)==1&&((*p)==1))&&(digitalRead(PIR7)==1&&((*q)==1)))&&(digitalRead(PIR1)==0&&digitalRead(PIR2)==0))
{
*count=(*count)+2;
EEPROM.write(0,*count);
*p==0;
EEPROM.write(1,*p);
*q==0;
EEPROM.write(2,*q);
}
else
if(((digitalRead(PIR1)==1&&((*r)==1))&&(digitalRead(PIR2)==1&&((*s)==1)))&&(digitalRead(PIR8)==0&&digitalRead(PIR7)==0))
{
*count=(*count)-2;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
*s==0;
EEPROM.write(5,*s);
}
else if(digitalRead(PIR2)==1&&((*s)==1)&&digitalRead(PIR7)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*s==0;
EEPROM.write(5,*s);
if(digitalRead(PIR1)==1&&((*r)==1)&&digitalRead(PIR8)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
}
else if(digitalRead(PIR8)==1&&((*r)==1)&&digitalRead(PIR1)==0)
{
*r==0;
EEPROM.write(4,*r);
}
else
{
}
}
else if(digitalRead(PIR7)==1&&((*s)==1)&&digitalRead(PIR2)==0)
{
*s==0;
EEPROM.write(5,*s);
if(digitalRead(PIR1)==1&&((*r)==1)&&digitalRead(PIR8)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
}
else if(digitalRead(PIR8)==1&&((*r)==1)&&digitalRead(PIR1)==0)
{
*r==0;
EEPROM.write(4,*r);
}
else
{
}
}
else if(digitalRead(PIR1)==1&&((*r)==1)&&digitalRead(PIR8)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
if(digitalRead(PIR2)==1&&((*s)==1)&&digitalRead(PIR7)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*s==0;
EEPROM.write(5,*s);
}
else if(digitalRead(PIR7)==1&&((*s)==1)&&digitalRead(PIR2)==0)
{
*s==0;
EEPROM.write(5,*s);
}
else
{
}
}
else if(digitalRead(PIR8)==1&&((*r)==1)&&digitalRead(PIR1)==0)
{
*r==0;
EEPROM.write(4,*r);
if(digitalRead(PIR2)==1&&((*s)==1)&&digitalRead(PIR7)==0)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*s==0;
EEPROM.write(5,*s);
}
else if(digitalRead(PIR7)==1&&((*s)==1)&&digitalRead(PIR2)==0)
{
*s==0;
EEPROM.write(5,*s);
}
else
{
}
}
else
{
}
}
void loop() 
{
do
{
if((digitalRead(PIR1)==1|| digitalRead(PIR2)==1)&&(digitalRead(PIR8)==0||digitalRead(PIR7)==0)&&digitalRead(PIR9)==1) /*
When passengers enters the train........ */
{
 delay(665);
/* ........then it checks whether a passenger enters the train by detecting IR 1. */
if(digitalRead(PIR1)==1&&digitalRead(PIR8)==0)
/* If PIR 1 detected but PIR 8 is undetected, the condition satisfies indicating that passenger is about to enter. After this
condition there are if-elseif-elseif-.....-else that shows whether this passenger is completely entered or not. */
{
if(digitalRead(PIR8)==0&&digitalRead(PIR7)==0) /* When the entered passenger doesn’t stand on the PIR 8, then…… */
{
Alerten==0; /* .......”Alerten” value becomes zero........ */
EEPROM.write(7,Alerten);
}
else /* ......otherwise....... */
{
Alerten==1; /* ........”Alerten” value becomes one. */
EEPROM.write(7,Alerten);
}
if(digitalRead(CNTACK)==1) /* ......and sends to Arduino used for Laser communication if receives an acknowledgement. */
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
delay(1200);
if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==0)) /* If PIR 8 is detected and
PIR 1 is undetected, then..... */
{
counter=counter+1; /* ......counter increments by one.......... */
EEPROM.write(8,counter);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&((digitalRead(PIR7)==0&&digitalRead(PIR2)==1)||(digitalRead(PIR2)==0&&digitalRead(PIR7)==1))) /* Same count
increment but the difference is that it detects at the time where PPIR2 is detected by next passenger who has started to enter. */
{
counter=counter+1;
EEPROM.write(8,counter);
continue; /* continue statement is used so that it will count the second passenger without delay. */
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)) /* This sub-loop
indicates the condition where two persons after crossing PIR 1 & 2 at distinct timings enters PIR 8 & 7 at the same time */
{
/* When Alerten=0, then count is incremented twice........*/
if(Alerten==0&&(digitalRead(PIR8)==1&&e1==1)&&digitalRead(PIR1)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(Alerten==0&&(digitalRead(PIR7)==1&&e2==1)&&digitalRead(PIR2)==0&& digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&(e1==1||e2==1)&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&e1==0&&e2==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
}
else if((Alerten==1&&e1==1)||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((Alerten==1&&e1==0)||digitalRead(PIR9)==1) /* ......otherwise count is incremented once because there are cases
where a person who is taken into count already may simply stand under PIR 7 or exit the train. This situation should not be
mistaken with the above sub-loop condition. So condition of PIR 1 or 2 detection is checked for two times at
the initial point of loop() function. */
{
counter=counter+1;
EEPROM.write(8,counter);
}
else
{
}
}
/* e1, e2, e8, e7 are the variables which becomes 1 when count variation doesn't takes place at the time of boarding or leaving the
train by the passenger. If a passenger stands between PIR 1 and 8 without entering,........ */
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
e1==1; /* ......then e1 becomes 1.*/
EEPROM.write(9,e1);
do /* This do.......while loop with e1 as 1 checks........ */
{
if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==0)) /* .........whether the
passenger has entered inside so that count is incremented and e1 becomes zero.......... */
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==0)) /* ...... or exited
so that e1 becomes zero and count is not varied. */
{
e1==0;
EEPROM.write(9,e1);
}
/* The following six conditions are same like the above two condition except the fact that it checks whether another
passenger crosses PIR 2 to 7 or 7 to 2. In case even after e1 as 1....... */
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==1))
{
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
e1==0;
EEPROM.write(9,e1);
}
else if(((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))) /* ........if the
passenger still remains in between PIR 1 & 8, compnx() function is called after making e2 as 1 and delay of 665 milliseconds if
next passenger is about to enter by crossing PIR 2.............*/
{
e2==1;
EEPROM.write(10,e2);
delay(665);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else if(((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))) /* ........ or
nocount1() function is called when a passenger is about to exit by crossing PIR 7 so that count variation is compensated. */
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
else
{
}
if(digitalRead(CNTACK)==1) /* If signal is received from Arduino placed at centre for communication purpose,............ */
{
Wire.beginTransmission(1);
Wire.write(counter); /* ........then Arduino at exits will transfer count details........... */
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH); /* ......and then sends the confirmation signal to that Arduino at centre. */
digitalWrite(CNTSNT,LOW);
}
}
while(e1==1);
continue; /* Then this statement will skip the remaining functions and then start from the beginning of do....while loop. */
}
/* The next else if conditions are same like previous conditional loop except the fact that next passenger is about to enter by
crossing PIR 2 first..... */
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
e1==1;
EEPROM.write(9,e1);
do
{
if(digitalRead(PIR8)==1&&digitalRead(PIR1)==0)
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(digitalRead(PIR1)==1&&digitalRead(PIR8)==0)
{
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==1))/* When a
passenger occurs between PIR 2&7 when previous passenger crosses PIR 8 from 1, then count is incremented once and this upcount function is called and this passenger after he / she
reaches PIR 7 is counted. */
{
counter=counter+1;
EEPROM.write(8,counter);
e2==1;
EEPROM.write(10,e2);
upcount(&e1,&e2,&e8,&e7,&counter,&Alerten);
}
else if(((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==1)))
{
e1==0;
EEPROM.write(9,e1);
e2==1;
EEPROM.write(10,e2);
upcount(&e1,&e2,&e8,&e7,&counter,&Alerten);
}
else
if(((digitalRead(PIR1)==1&&digitalRead(PIR8)==1)&&(digitalRead(PIR2)==1&&(digitalRead(PIR7)==1||digitalRead(PIR7)==0))))
{
e2==1;
EEPROM.write(10,e2);
delay(665);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR1)==0&&digitalRead(PIR2)==0))
{
if(Alerten==0&&(digitalRead(PIR8)==1&&e1==1)&&digitalRead(PIR1)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(Alerten==0&&(digitalRead(PIR7)==1&&e2==1) &&digitalRead(PIR2)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&(e1==1||e2==1) &&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&e1==0&&e2==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
}
else if((Alerten==1&&e1==1)||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((Alerten==1&&e1==0) ||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
}
else
{
}
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e1==1);
continue;
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0)) /* .......... or exit by
crossing PIR 7 first so that count can be compensated using nocount1() function. */
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
/* nocount1 function is used when one passenger enters by crossing from PIR1 to 8 and another passenger exits by crossing from
PIR 7 to 2. nocount2 function is used for movement from PIR 2 to 7 for entry purpose and PIR 8 to 1 for exit purpose. */
}
else /* When passenger does not cross PIR 8 after crossing PIR 1, then...... */
{
Alertex==1; /* Alertex is incremented which is used when passengers crosses PIR 1 & 2 at same time whom crosses PIR 8 &
7 at different times. */
EEPROM.write(11,Alertex);
} /* Sub-loop ends */
if(digitalRead(PIR8)==0&&digitalRead(PIR7)==0) /* After counter increment when the entered person doesn’t stand on the
PIR 8, then…… */
{
Alerten==0; /* .......”Alerten” value becomes zero........ */
EEPROM.write(7,Alerten);
}
else /* ......otherwise....... */
{
Alerten==1; /* ........”Alerten” value becomes one. */
EEPROM.write(7,Alerten);
}
} /* The above loop for PIR 1 and 8 detection is completed. */
/* The same procedure is followed for detection of PIR 2 and 7 as follows but the difference is......... */
else if(digitalRead(PIR2)==1&&digitalRead(PIR7)==0)
{
if(digitalRead(PIR8)==0&&digitalRead(PIR7)==0)
{
Alerten==0;
EEPROM.write(7,Alerten);
}
else
{
Alerten==1;
EEPROM.write(7,Alerten);
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
delay(655);
if(digitalRead(PIR2)==1&&(digitalRead(PIR9)==1||digitalRead(PIR9)==0)&&digitalRead(PIR7)==0) /* .....Arduino checks for
PIR 9 detection after 665 milliseconds delay. */
{
delay(665);
/* Then after the same delay conditions is checked whether passenger crosses PIR 7 or stands between PIR 2 and 7.*/
if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==0))
{
counter=counter+1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&((digitalRead(PIR8)==0&&digitalRead(PIR1)==1)||(digitalRead(PIR8)==1&&digitalRead(PIR1)==0)))
{
counter=counter+1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR8)==1)&&(digitalRead(PIR2)==0&&digitalRead(PIR1)==0))
{
if(Alerten==0&&(digitalRead(PIR8)==1&e1==1)&&digitalRead(PIR1)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(Alerten==0&&(digitalRead(PIR7)==1&e2==1)&&digitalRead(PIR2)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(0,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&(e1==1||e2==1)&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&e1==0&&e2==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
}
else if((Alerten==1&&e2==1)||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==1&&e2==0||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
}
else
{
}
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
e2==1;
EEPROM.write(10,e2);
do
{
if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==0))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==0))
{
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==1))
{
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==1))
{
e1==1;
EEPROM.write(9,e1);
delay(665);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e2==1);
continue;
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
e2==1;
EEPROM.write(10,e2);
do
{
if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==1))
{
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
e1==1;
EEPROM.write(9,e1);
upcount(&e1,&e2,&e8,&e7,&counter,&Alerten);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==1))
{
e2==0;
EEPROM.write(10,e2);
e1==1;
EEPROM.write(9,e1);
upcount(&e1,&e2,&e8,&e7,&counter,&Alerten);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR8)==1&&(digitalRead(PIR1)==1||digitalRead(PIR1)==0))
{
e1==1;
EEPROM.write(9,e1);
delay(665);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR8)==1)&&(digitalRead(PIR2)==0&&digitalRead(PIR1)==0))
{
if(Alerten==0&&(digitalRead(PIR8)==1&e1==1)&&digitalRead(PIR1)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(Alerten==0&&(digitalRead(PIR7)==1&e2==1)&&digitalRead(PIR2)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(0,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&(e1==1||e2==1)&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&e1==0&&e2==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
}
else if((Alerten==1&&e2==1)||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==1&&e2==0||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
}
else
{
}
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e2==1);
continue;
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
if(digitalRead(PIR8)==0&&digitalRead(PIR7)==0)
{
Alerten==0;
EEPROM.write(7,Alerten);
}
else
{
Alerten==1;
EEPROM.write(7,Alerten);
}
}
}
/* If two persons crosses PIR 1 & 2 at the same time, then….. */
else if((digitalRead(PIR1)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==0&&digitalRead(PIR7)==0))
{
if(digitalRead(PIR8)==0&&digitalRead(PIR7)==0)
{
Alerten==0;
EEPROM.write(7,Alerten);
}
else
{
Alerten==1;
EEPROM.write(7,Alerten);
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
delay(655);
if(digitalRead(PIR9)==1&&digitalRead(PIR1)==1&&digitalRead(PIR2)==1&&digitalRead(PIR8)==1&&digitalRead(PIR7)==1) /*
PIR 9 is placed between PIR 2, 7 and 10. This prevents twice increment when one passenger itself crosses two sensors PIR 1 and
2. Similarly PIR 10 is placed between PIR 4, 5 and 9 to prevent double count for detection of both PIR 3 and 4 by one passenger.
*/
/* Even for same-time of PIR 8 & 7 detection after PIR 1 & 2 detection at different timings, PIR 9 will identify whether the
second passenger is entering if PIR9 is detected or about to exit if PIR9 is not detected. */
{
delay(665);
if((digitalRead(PIR8)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)) /* If PIR 8 & 7 detected
when 1,2 not detected then….... */
{ /* ...........count is incremented twice. */
if((digitalRead(PIR8)==1&&e1==1)&&digitalRead(PIR1)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR7)==1&&e2==1) &&digitalRead(PIR2)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else
{
counter=counter+2;
EEPROM.write(8,counter);
}
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR1)==1&&digitalRead(PIR2)==1)) /* When all PIR’s
detected, then…… */
{
e1==1;
EEPROM.write(9,e1);
e2==1;
EEPROM.write(10,e2);
delay(665);
compnx(&e8,&e7,&e1,&e2,&counter); /* e1 and e2 becomes 1 and compnx() function is called after delay of 665 milliseconds.
*/
}
/* if double count doesn't happen, then checks for single count. These loops used to check PIR 2 to 7 detection which follows
the same as before. */
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==0))
{
counter=counter+1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&((digitalRead(PIR8)==0&&digitalRead(PIR1)==1)||(digitalRead(PIR8)==1&&digitalRead(PIR1)==0)))
{
counter=counter+1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
e1==1;
EEPROM.write(9,e1);
upcount(&e1,&e2,&e8,&e7,&counter,&Alerten);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
e2==1;
EEPROM.write(10,e2);
do
{
if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==0))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==0))
{
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==1))
{
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==1))
{
e1==1;
EEPROM.write(9,e1);
delay(665);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e2==1);
continue;
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
e2==1;
EEPROM.write(10,e2);
do
{
if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==1))
{
e2==0;
EEPROM.write(10,e2);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
e1==1;
EEPROM.write(9,e1);
upcount(&e1,&e2,&e8,&e7,&counter,&Alerten);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==1))
{
e2==0;
EEPROM.write(10,e2);
e1==1;
EEPROM.write(9,e1);
upcount(&e1,&e2,&e8,&e7,&counter,&Alerten);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR8)==0&&(digitalRead(PIR1)==1||digitalRead(PIR1)==0)))
{
e1==1;
EEPROM.write(9,e1);
delay(665);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR8)==1)&&(digitalRead(PIR2)==0&&digitalRead(PIR1)==0))
{
if(Alerten==0&&(digitalRead(PIR8)==1&e1==1)&&digitalRead(PIR1)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(Alerten==0&&(digitalRead(PIR7)==1&e2==1)&&digitalRead(PIR2)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(0,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&(e1==1||e2==1)&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&e1==0&&e2==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
}
else if((Alerten==1&&e2==1)||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==1&&e2==0||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
}
else
{
}
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e2==1);
continue;
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
}
}
/* If PIR 9 is not detected after 665 milliseconds delay, then it indicates that one passenger only enters as shown by PIR 1 to 8
detection conditions at the following. */
if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==0))
{
counter=counter+1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&((digitalRead(PIR7)==0&&digitalRead(PIR2)==1)||(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
counter=counter+1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR1)==0&&digitalRead(PIR2)==0))
{
if(Alerten==0&&(digitalRead(PIR8)==1&&e1==1)&&digitalRead(PIR1)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(Alerten==0&&(digitalRead(PIR7)==1&&e2==1)&&digitalRead(PIR2)==0&& digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&(e1==1||e2==1)&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&e1==0&&e2==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
}
else if((Alerten==1&&e1==1)||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((Alerten==1&&e1==0) ||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
}
else
{
}
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
e1==1;
EEPROM.write(9,e1);
do
{
if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==0))
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==0))
{
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==1))
{
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
e1==0;
EEPROM.write(9,e1);
}
else if(((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0)))
{
e2==1;
EEPROM.write(10,e2);
delay(665);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else if(((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0)))
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e1==1);
continue;
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
e1==1;
EEPROM.write(9,e1);
do
{
if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==1))
{
e1==0;
EEPROM.write(9,e1);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==1))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==1;
EEPROM.write(10,e2);
upcount(&e1,&e2,&e8,&e7,&counter,&Alerten);
}
else if(((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==1)))
{
e1==0;
EEPROM.write(9,e1);
e2==1;
EEPROM.write(10,e2);
upcount(&e1,&e2,&e8,&e7,&counter,&Alerten);
}
else
if(((digitalRead(PIR1)==1&&digitalRead(PIR8)==1)&&(digitalRead(PIR2)==1&&(digitalRead(PIR7)==1||digitalRead(PIR7)==0))))
{
e2==1;
EEPROM.write(10,e2);
delay(665);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR1)==0&&digitalRead(PIR2)==0))
{
if(Alerten==0&&(digitalRead(PIR8)==1&&e1==1)&&digitalRead(PIR1)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(Alerten==0&&(digitalRead(PIR7)==1&&e2==1) &&digitalRead(PIR2)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&(e1==1||e2==1) &&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&e1==0&&e2==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
}
else if((Alerten==1&&e1==1)||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((Alerten==1&&e1==0) ||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
}
else
{
}
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e1==1);
continue;
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
if(digitalRead(PIR8)==0&&digitalRead(PIR7)==0)
{
Alerten==0;
EEPROM.write(17,Alerten);
}
else
{
Alerten==1;
EEPROM.write(17,Alerten);
}
}
else
{
}
}
/* So far the above loops increments the count either once or twice. Now the following loops for once or twice count decrement.
If PIR 8 is detected and then after PIR 1 is detected, then count is decremented indicating that the passenger exits the train. If
not following sub or sub-sub loops are followed or Alerten is incremented. */
else if((digitalRead(PIR8)==1|| digitalRead(PIR7)==1)&&(digitalRead(PIR1)==0||digitalRead(PIR2)==0)) /* When a person is
about to exit the train. */
{
delay(665);
if((digitalRead(PIR8)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)) /* Twice decrement. */
{
if(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)
{
Alertex==0;
EEPROM.write(11,Alertex);
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
delay(665);
/* PIR 3 is also used for reducing twice decrement by one person like PIR 9. */
if(digitalRead(PIR9)==1&&digitalRead(PIR3)==1&&digitalRead(PIR6)==1&&digitalRead(PIR1)==1&&digitalRead(PIR2)==1&&digitalRead(PIR8)==1&&digitalRead(PIR7)==1)
{
delay(665);
if((digitalRead(PIR1)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==0&&digitalRead(PIR7)==0))
{
if((digitalRead(PIR1)==1&e8==1) &&digitalRead(PIR8)==0)
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR2)==1&&e7==1) &&digitalRead(PIR7)==0)
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else
{
counter=counter-2;
EEPROM.write(8,counter);
}
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==1&&digitalRead(PIR7)==1))
{
e8==1;
EEPROM.write(12,e8);
e7==1;
EEPROM.write(13,e7);
delay(665);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&((digitalRead(PIR1)==0&&digitalRead(PIR8)==1)||(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==1))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
e8==1;
EEPROM.write(12,e8);
downcount(&e1,&e2,&e8,&e7,&counter,&Alertex);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==0))
{
e7==1;
EEPROM.write(11,e7);
do
{
if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==1;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
e7==0;
EEPROM.write(8,e7);
e8==1;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
e8==1;
EEPROM.write(12,e8);
delay(665);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e7==1);
continue;
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
e7==1;
EEPROM.write(11,e7);
do
{ 
if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==1))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
e8==1;
EEPROM.write(12,e8);
downcount(&e1,&e2,&e8,&e7,&counter,&Alertex);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==1))
{
e7==0;
EEPROM.write(8,e7);
e8==1;
EEPROM.write(12,e8);
downcount(&e1,&e2,&e8,&e7,&counter,&Alertex);
}
else
if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==1&&(digitalRead(PIR1)==1||digitalRead(PIR1)==0)))
{
e8==1;
EEPROM.write(12,e8);
delay(665);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==0&&digitalRead(PIR8)==0))
{
if(Alertex==0&&digitalRead(PIR2)==1&&e7==1&&digitalRead(PIR7)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==0&&digitalRead(PIR1)==1&&e8==1&&digitalRead(PIR8)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&(e8==1||e7==1)&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&e8==0&&e7==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
}
else if((Alertex==1&&e7==1)||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==1||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
}
else
{
}
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e7==1);
continue;
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
else
{
}
}
if(digitalRead(PIR9)==0)
{
if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)) /* Count decrement by detection of PIR 8 and 1. */
{
if(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)
{
Alertex==0;
EEPROM.write(11,Alertex);
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
delay(1200);
if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&((digitalRead(PIR2)==0&&digitalRead(PIR7)==1)||(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==0&&digitalRead(PIR7)==0))
{
if(Alertex==0&&(digitalRead(PIR2)==1&&e7==1)&&digitalRead(PIR7)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==0&&(digitalRead(PIR1)==1&&e8==1)&&digitalRead(PIR8)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&e7==0&&e8==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
}
else if(Alertex==1||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((Alertex==1&&e8==1)||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else
{
}
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==1)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==0))
{
e8==1;
EEPROM.write(12,e8);
do
{ 
if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==1))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==1))
{
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
e7==1;
EEPROM.write(13,e7);
delay(665);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e8==1);
continue;
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==1)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
e8==1;
EEPROM.write(12,e8);
do
{ 
if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==1))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==1))
{
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==1))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
e7==1;
EEPROM.write(13,e7);
downcount(&e1,&e2,&e8,&e7,&counter,&Alertex);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==1))
{
e8==0;
EEPROM.write(12,e8);
e7==1;
EEPROM.write(13,e7);
downcount(&e1,&e2,&e8,&e7,&counter,&Alertex);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
e7==1;
EEPROM.write(13,e7);
delay(665);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==0&&digitalRead(PIR7)==0))
{
if(Alertex==0&&(digitalRead(PIR2)==1&&e7==1)&&digitalRead(PIR7)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==0&&(digitalRead(PIR1)==1&&e8==1)&&digitalRead(PIR8)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&e7==0&&e8==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
}
else if(Alertex==1||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((Alertex==1&&e8==1)||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else
{
}
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e8==1);
continue;
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
}
}
else
{
Alerten==1;
EEPROM.write(17,Alerten);
}
}
if(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)
{
Alertex==0;
EEPROM.write(11,Alertex);
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
/* Now two else if statements occurs for single count decrement by detection from PIR 7 to 2 or PIR 8 to 1. */
else if(digitalRead(PIR7)==1&&digitalRead(PIR6)==1&&digitalRead(PIR2)==0)
{
if(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)
{
Alertex==0;
EEPROM.write(11,Alertex);
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
delay(655);
if((digitalRead(PIR9)==1||digitalRead(PIR9)==0)&&digitalRead(PIR3)==1&&digitalRead(PIR6)==1) /* Since PIR 2, 3,6 & 7 are
very close, PIR3 detection will indicate that two passengers are exiting and condition satisfies. If not then count is not varied as
PIR 6 to 3 detection will decrement the count with the help of another Arduino. Every exits has two Arduinos. */
{
delay(665);
if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==1))
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==0&&digitalRead(PIR8)==0))
{
if(Alertex==0&&digitalRead(PIR2)==1&&e7==1&&digitalRead(PIR7)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==0&&digitalRead(PIR1)==1&&e8==1&&digitalRead(PIR8)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&(e8==1||e7==1)&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&e8==0&&e7==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
}
else if((Alertex==1&&e7==1)||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==1||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
}
else
{
}
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==0&&digitalRead(PIR1)==0))
{
e7==1;
EEPROM.write(11,e7);
do
{ 
if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==1;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
e7==0;
EEPROM.write(8,e7);
e8==1;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
e8==1;
EEPROM.write(12,e8);
delay(665);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e7==1);
continue;
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
e7==1;
EEPROM.write(11,e7);
do
{ 
if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR1)==0&&digitalRead(PIR8)==0))
{
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
e7==0;
EEPROM.write(11,e7);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR7)==0)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==1))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(8,e7);
e8==1;
EEPROM.write(12,e8);
downcount(&e1,&e2,&e8,&e7,&counter,&Alertex);
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==0)&&(digitalRead(PIR8)==1&&digitalRead(PIR1)==1))
{
e7==0;
EEPROM.write(8,e7);
e8==1;
EEPROM.write(12,e8);
downcount(&e1,&e2,&e8,&e7,&counter,&Alertex);
}
else
if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==1&&(digitalRead(PIR1)==1||digitalRead(PIR1)==0)))
{
e8==1;
EEPROM.write(12,e8);
delay(665);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==0&&digitalRead(PIR8)==0))
{
if(Alertex==0&&digitalRead(PIR2)==1&&e7==1&&digitalRead(PIR7)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==0&&digitalRead(PIR1)==1&&e8==1&&digitalRead(PIR8)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&(e8==1||e7==1)&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&e8==0&&e7==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
}
else if((Alertex==1&&e7==1)||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==1||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
}
else
{
}
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e7==1);
continue;
}
else if((digitalRead(PIR7)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR1)==1&&digitalRead(PIR8)==0))
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
else
{
Alerten==1;
EEPROM.write(7,Alerten);
}
}
if(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)
{
Alertex==0;
EEPROM.write(11,Alertex);
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0))
{
if(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)
{
Alertex==0;
EEPROM.write(11,Alertex);
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
delay(900);
if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==1))
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==0&&digitalRead(PIR7)==0))
{
if(Alertex==0&&(digitalRead(PIR2)==1&&e7==1)&&digitalRead(PIR7)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==0&&(digitalRead(PIR1)==1&&e8==1)&&digitalRead(PIR8)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&e7==0&&e8==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
}
else if(Alertex==1||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((Alertex==1&&e8==1)||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else
{
}
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==1)&&(digitalRead(PIR7)==0&&digitalRead(PIR2)==0))
{
e8==1;
EEPROM.write(12,e8);
do
{ if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==1))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==1))
{
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
e7==1;
EEPROM.write(13,e7);
delay(665);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e8==1);
continue;
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==1)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
e8==1;
EEPROM.write(12,e8);
do
{ 
if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==0))
{
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==1))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==0&&digitalRead(PIR7)==1))
{
e8==0;
EEPROM.write(12,e8);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==1))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
e7==1;
EEPROM.write(13,e7);
downcount(&e1,&e2,&e8,&e7,&counter,&Alertex);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==1))
{
e8==0;
EEPROM.write(12,e8);
e7==1;
EEPROM.write(13,e7);
downcount(&e1,&e2,&e8,&e7,&counter,&Alertex);
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
e7==1;
EEPROM.write(13,e7);
delay(665);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((digitalRead(PIR1)==1&&digitalRead(PIR2)==1)&&(digitalRead(PIR8)==0&&digitalRead(PIR7)==0))
{
if(Alertex==0&&(digitalRead(PIR2)==1&&e7==1)&&digitalRead(PIR7)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==0&&(digitalRead(PIR1)==1&&e8==1)&&digitalRead(PIR8)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&e7==0&&e8==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
}
else if(Alertex==1||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((Alertex==1&&e8==1)||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else
{
}
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(e8==1);
continue;
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
else
{
Alerten==1;
EEPROM.write(7,Alerten);
}
if(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)
{
Alertex==0;
EEPROM.write(11,Alertex);
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
}
/* If the process is interrupted due to power cut, then e1, e2, e8 & e7 will be used to count passengers as shown in following
loops below. */
else if((digitalRead(PIR1)==1&&e1==1&&digitalRead(PIR8)==0)&&(digitalRead(PIR7)==1&&digitalRead(PIR2)==0))
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
continue;
}
else
if((digitalRead(PIR8)==1&&e1==1&&digitalRead(PIR1)==0)&&((digitalRead(PIR2)==1||digitalRead(PIR2)==0)&&digitalRead(PIR7)==0))
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
continue;
}
else
if((digitalRead(PIR7)==1&&e2==1&&digitalRead(PIR2)==0)&&((digitalRead(PIR1)==1||digitalRead(PIR1)==0)&&digitalRead(PIR8)==0))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
continue;
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR7)==1)&&(digitalRead(PIR1)==0&&digitalRead(PIR2)==0)&&(e1==1||e2==1))
{ if(Alerten==0&&(digitalRead(PIR8)==1&&e1==1)&&digitalRead(PIR1)==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(Alerten==0&&(digitalRead(PIR7)==1&&e2==1)&&digitalRead(PIR2)==0&& digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&(e1==1||e2==1)&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&e1==0&&e2==0&&digitalRead(PIR9)==0)
{
counter=counter+2;
EEPROM.write(8,counter);
}
else if((Alerten==1&&e1==1)||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((Alerten==1&&e1==0) ||digitalRead(PIR9)==1)
{
counter=counter+1;
EEPROM.write(8,counter);
}
else
{
}
}
else if((digitalRead(PIR2)==1&&digitalRead(PIR1)==1)&&(digitalRead(PIR7)==0&&digitalRead(PIR8)==0)&&(e7==1||e8==1))
{
if(Alertex==0&&digitalRead(PIR2)==1&&e7==1&&digitalRead(PIR7)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==0&&digitalRead(PIR1)==1&&e8==1&&digitalRead(PIR8)==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&(e8==1||e7==1)&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&e8==0&&e7==0&&digitalRead(PIR9)==0)
{
counter=counter-2;
EEPROM.write(8,counter);
}
else if((Alertex==1&&e7==1)||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==1||digitalRead(PIR9)==1)
{
counter=counter-1;
EEPROM.write(8,counter);
}
else
{
}
}
else
if((digitalRead(PIR1)==1&&e8==1&&digitalRead(PIR8)==0)&&((digitalRead(PIR7)==1||digitalRead(PIR7)==0)&&digitalRead(PIR2)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
continue;
}
else
if((digitalRead(PIR2)==1&&e7==1&&digitalRead(PIR7)==0)&&((digitalRead(PIR8)==1||digitalRead(PIR8)==0)&&digitalRead(PIR1)==0))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
continue;
}
else if((digitalRead(PIR8)==1&&digitalRead(PIR1)==0)&&(digitalRead(PIR2)==1&&digitalRead(PIR7)==0))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
continue;
}
else
{
}
if(digitalRead(CNTACK)==1)
{
Wire.beginTransmission(1);
Wire.write(counter);
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
}
while(0<counter<160);
}
