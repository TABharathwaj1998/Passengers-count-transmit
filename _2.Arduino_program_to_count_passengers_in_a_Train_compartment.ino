/* Arduino program to count passengers in a Train compartment */
#include<EEPROM.h> /* EEPROM is used for permanent storage of variables which will prevent erasing of values when the power is switched OFF. */
#include<Wire.h>
int LDR1=A0;
int LDR2=A1;
int LDR9=A2;
int LDR7=A3;
int LDR8=A4;
int LDR=A5;
int Lightctrl=A6;
int EXTLDR=A7;
/* LDR (Light dependant resistor) is used for counting the passengers. */
#define LIGHT 22
#define CNTACK 30
#define CNTSNT 3
extern int ldr1, ldr2, ldr9, ldr7, ldr8, ldr, temp, Lock, diff, diff9, temp9, tensldr9, Lock9, ld, extld, counter=0, c=0, *count=0, a=0, flag=0, e1=0, e2=0, e7=0, e8=0, *p=0, *q=0, *r=0, *s=0, eoe=0, Alerten=0, *ena=0, Alertex=0, *exa=0;
void ldr();
void ldr18();
void nocount1(int *p,int *s,int *count,int *ena,int *exa);
void ldr27();
void compnx(int *r, int *s, int *p, int*q, int *count);
void ldr72();
void nocount2(int *q,int *r,int *count,int *ena,int *exa);
void ldr81();
/* Ten call by pointer functions described above are used to make the counting process with minimum errors and delays. */
void setup()
{
pinMode(LIGHT, OUTPUT);
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
temp=EEPROM.read(14);
Lock=EEPROM.read(15);
diff=EEPROM.read(16);
diff9=EEPROM.read(17);
temp=EEPROM.read(18);
tensldr9=EEPROM.read(19);
Lock9=EEPROM.read(20);
}
void ldr()    /* To measure light intensity using....... */
{     
Id=analogRead(Lightctrl);
if(ld>600)     /* .......ld variable.........*/
{
digitalWrite(LIGHT, HIGH); /*...... to switch ON /....... */
}
else
{
digitalWrite(LIGHT, LOW);   /*....... OFF the lights inside the train compartment and .......... */
}
ldr=analogRead(LDR);      /* ldr to detect light intensity at compartment exits so that..............*/
temp=ldr/100;
EEPROM.write(14,temp); 
Lock=(temp+1)*100;      /*......... adding Hundredth digit of ldr value with 1 and multiplying it totally by 100 gives “Lock” variable. */
EEPROM.write(15,Lock);
ldr1=analogRead(LDR1);
ldr2=analogRead(LDR2);
ldr9=analogRead(LDR9);
ldr7=analogRead(LDR7);
ldr8=analogRead(LDR8);  
/* All LDRs that are within certain limits as shown below are subtracted.......... */
if(((500<ldr1<600)&&(500<ldr2<600)&&(500<ldr8<600)&&(500<ldr7<600))|| ((ldr1>600)&&(500<ldr2<600)&&(500<ldr8<600)&&(500<ldr7<600))|| ((500<ldr1<600)&&(ldr2>600)&&(500<ldr8<600)&&(500<ldr7<600))|| ((500<ldr1<600)&&(500<ldr2<600)&&(ldr8>600)&&(500<ldr7<600))|| ((500<ldr1<600)&&(500<ldr2<600)&&(500<ldr8<600)&&(ldr7>600))|| ((ldr1>600)&&(ldr2>600)&&(500<ldr8<600)&&(500<ldr7<600))|| ((500<ldr1<600)&&(500<ldr2<600)&&(ldr8>600)&&(ldr7>600))|| ((ldr1>600)&&(500<ldr2<600)&&(500<ldr8<600)&&(ldr7>600))|| ((500<ldr1<600)&&(ldr2>600)&&(500<ldr8<600)&&(ldr7>600))|| ((ldr1>600)&&(ldr2>600)&&(ldr8>600)&&(ldr7>600)&&(ldr>600))
{
if(temp==3)
{
diff=2;
EEPROM.write(16,diff);
}
else if(temp==4)
{
diff=1;
EEPROM.write(16,diff);
}
else
{
if(temp==5)
{
diff=0;
EEPROM.write(16,diff);
}
}
}
else if(((600<ldr1<700)&&(600<ldr2<700)&&(600<ldr8<700)&&(600<ldr7<700))|| ((ldr1>700)&&(600<ldr2<700)&&(600<ldr8<700)&&(600<ldr7<700))|| ((600<ldr1<700)&&(ldr2>700)&&(600<ldr8<700)&&(600<ldr7<700))|| ((600<ldr1<700)&&(600<ldr2<700)&&(ldr8>700)&&(600<ldr7<700))|| ((600<ldr1<700)&&(600<ldr2<700)&&(600<ldr8<700)&&(ldr7>700))|| ((ldr1>700)&&(ldr2>700)&&(600<ldr8<700)&&(600<ldr7<700))|| ((600<ldr1<700)&&(600<ldr2<700)&&(ldr8>700)&&(ldr7>700))|| ((ldr1>700)&&(600<ldr2<700)&&(600<ldr8<700)&&(ldr7>700))|| ((600<ldr1<700)&&(ldr2>700)&&(600<ldr8<700)&&(ldr7>700))|| ((ldr1>700)&&(ldr2>700)&&(ldr8>700)&&(ldr7>700)&&(ldr>600))
{
if(temp==3)
{
diff=3;
EEPROM.write(16,diff);
}
else if(temp==4)
{
diff=2;
EEPROM.write(16,diff);
}
else if(temp==5)
{
diff=1;
EEPROM.write(16,diff);
}
else
{
if(temp==6)
{
diff=0;
EEPROM.write(16,diff);
}
}
}
else if(((700<ldr1<800)&&(700<ldr2<800)&&(700<ldr8<800)&&(700<ldr7<800))|| ((ldr1>800)&&(700<ldr2<800)&&(700<ldr8<800)&&(700<ldr7<800))|| ((700<ldr1<800)&&(ldr2>800)&&(700<ldr8<800)&&(700<ldr7<800))|| ((700<ldr1<800)&&(700<ldr2<800)&&(ldr8>800)&&(700<ldr7<800))|| ((700<ldr1<800)&&(700<ldr2<800)&&(700<ldr8<800)&&(ldr7>800))|| ((ldr1>800)&&(ldr2>800)&&(700<ldr8<800)&&(700<ldr7<800))|| ((700<ldr1<800)&&(700<ldr2<800)&&(ldr8>800)&&(ldr7>800))|| ((ldr1>800)&&(700<ldr2<800)&&(700<ldr8<800)&&(ldr7>800))|| ((700<ldr1<800)&&(ldr2>800)&&(700<ldr8<800)&&(ldr7>800))|| ((ldr1>800)&&(ldr2>800)&&(ldr8>800)&&(ldr7>800)&&(ldr>600))
{
if(temp==3)
{
diff=4;
EEPROM.write(16,diff);
}
else if(temp==4)
{
diff=3;
EEPROM.write(16,diff);
}
else if(temp==5)
{
diff=2;
EEPROM.write(16,diff);
}
else if(temp==6)
{
diff=1;
EEPROM.write(16,diff);
}
else
{
if(temp==7)
{
diff=0;
EEPROM.write(16,diff);
}
}
}
else
{
}
/*..........with “diff” value depending upon the “temp” value. For instance if the “temp” value is 4 and ldr 1, 2, 8 or 7 has values ranging between 500 and 600, then “diff” value will be 1 for making ldr 1, 2, 7 and 8 range between values which ldr ranges. */
ldr1=ldr1-(diff*100);  
ldr2=ldr2-(diff*100);
ldr8=ldr8-(diff*100);
ldr7=ldr7-(diff*100);
/* ldr 9 is same like others except the fact that Lock9 =Lock - 50 if tens digit of ldr 9 is between 0 and 50 or Lock9==Lock if between 50 and 100. */
if((600<ldr9<700)&&(ldr1<Lock||ldr2<Lock||ldr7<Lock||ldr8<Lock))
{
if(temp==3)
{
diff9=3;
EEPROM.write(17,diff9);
}
else if(temp==4)
{
diff9=2;
EEPROM.write(17,diff9);
}
else if(temp==5)
{
diff9=1;
EEPROM.write(17,diff9);
}
else
{
if(temp==6)
{
diff9=0;
EEPROM.write(17,diff9);
}
}
}
else if((700<ldr9<800)&&( ldr1<Lock||ldr2<Lock||ldr7<Lock||ldr8<Lock))
{
if(temp==3)
{
diff9=4;
EEPROM.write(17,diff9);
}
else if(temp==4)
{
diff9=3;
EEPROM.write(17,diff9);
}
else if(temp==5)
{
diff9=2;
EEPROM.write(17,diff9);
}
else if(temp==6)
{
diff9=1;
EEPROM.write(17,diff9);
}
else
{
if(temp==7)
{
diff9=0;
EEPROM.write(17,diff9);
}
}
}
else
{
if((ldr9>600)&&((ldr1>Lock&&ldr8>Lock)||(ldr7>Lock&&ldr2>Lock)))
{
}
}
ldr9=ldr9-(diff9*100);
temp9=ldr9/100;
EEPROM.write(18,temp9);
tensldr9=ldr9-(temp9-100);
EEPROM.write(19,tensldr9);
if(0<=tensldr9<50)
{
Lock9=Lock-50;
EEPROM.write(20,Lock9);
}
else
{
if(50<=tensldr9<100)
{
Lock9==Lock;
EEPROM.write(20,Lock9);
}
} /* So light is obstructed by passengers movement inside or outside if Ldrs value are greater than the Lock value. */
} 
void loop() 
{
do
{
ldr();   /* To call ldr function for light intensity detection. */
if(ldr1>Lock&&ldr8<Lock)  /* If LDR 1 detects passenger's movement and LDR 8 detects nothing, the condition satisfies indicating that passenger is about to enter. After this condition there are if-elseif-elseif-.....-else that shows whether this passenger completely enters or not. */
{
ldr();   
if(ldr8<Lock&&ldr7<Lock) 
{
Alerten==0; 
EEPROM.write(7,Alerten);
}
else 
{
Alerten==1; /* ”Alerten” variable avoids twice increment by one passenger. */
EEPROM.write(7,Alerten);
}
delay(665);
if(ldr9<Lock9) /* If ldr9 value is less than lock, then one passenger only enters. */
{
if((ldr8>Lock&&ldr1<Lock)&&(ldr7<Lock&&ldr2<Lock)) /* If LDR 8 detects and LDR 1 not, then..... */
{
counter=counter+1; /* ......counter increments by one. */
EEPROM.write(8,counter);
}
else if((ldr8>Lock&&ldr1<Lock)&&((ldr7<Lock&&ldr2>Lock)||(ldr2<Lock&&ldr7>Lock))) /* Else same count increment with LDR2 detecting next passenger who is about to enter. */
{
counter=counter+1;
EEPROM.write(8,counter);
continue; /* continue statement skips the remaining function and counts the second passenger without delay. */
}
/* e1, e2, e8, e7 are the variables which becomes 1 or 2 when a passenger stands between LDR 1 and 8 or 2 and 7*/
else if((ldr8>Lock&&ldr1>Lock)&&(ldr2<Lock&&ldr7<Lock)) /* If entering passenger stands between 1 and 8,........ */
{
e1==1; /* ...... e1 becomes 1............ */
EEPROM.write(9,e1);
ldr18();  /*.........and this function is called to check whether this passenger had boarded or not. */
continue;   /* Then this statement will skip the remaining functions and then start from the beginning of do....while loop. */
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr2>Lock&&ldr7<Lock))   /* Same LDR 1 & 8 at same time with difference that next passenger is about to enter by crossing LDR 2 first and e1 becomes 2. */
{
e1==2;
EEPROM.write(9,e1);
ldr18();
continue;
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr7>Lock&&ldr2<Lock)) 
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
/* nocount1 function is used when one passenger enters by crossing from LDR1 to 8 and another passenger exits by crossing from LDR 7 to 2. nocount2 function is used for movement from LDR 2 to 7 for entry purpose and LDR 8 to 1 for exit purpose. */
}
else /* When passenger does not cross LDR 8 after crossing LDR 1, then...... */
{
Alertex==1; /* Alertex is incremented. */
EEPROM.write(11,Alertex);
} /* Sub-loop ends */
}
else if(ldr9>Lock9&&ldr2>Lock)  /* ldr9 and 2 greater than Lock indicates that two passenger enters at a same time. */
{
 delay(655);
 if((ldr8>Lock&&ldr7>Lock)&&(ldr1<Lock&&ldr2<Lock)) /* This sub-loop indicates the condition where two passengers after crossing LDR 1 & 2 at distinct timings crosses LDR 8 & 7 at the same time resulting in twice count increment.  */
{
/* When Alerten=0, then count is incremented twice........*/
if(Alerten==1) /* ......otherwise count is incremented once because there are cases where a person who is taken into count already may simply stand under LDR 7 which should not be mistaken with this sub-loop condition. */
{
counter=counter+1;
EEPROM.write(8,counter);
}
else
{
counter=counter+2;
EEPROM.write(8,counter);
}
}
else /* If no ldr8 & 7 detection, then .......... */
{
e1==1;              
EEPROM.write(9,e1);
e2==1;
EEPROM.write(10,e2);
while(e1==1&&e2==1)
{
compnx(&e8,&e7,&e1,&e2,&counter);   /*.........this function compensates depending on the entry or exit of passengers. */
}
}
}
else if(ldr9<Lock9&&ldr7>Lock).  /* If ldr7 greater instead of ldr2 along with ldr9, then nocount1 function is used. */
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);    
}
else
{
}
if(ldr8<Lock&&ldr7<Lock)  /* After counter increment when the entered person doesn’t stand on the LDR 8, then…… */
{
Alerten==0; /* .......”Alerten” value becomes zero........ */
EEPROM.write(7,Alerten);
}
else /* ......otherwise....... */
{
Alerten==1; /* ........”Alerten” value becomes one. */
EEPROM.write(7,Alerten);
}
if(digitalRead(CNTACK)==1) /* Acknowledgement received from Arduino A7 or A9........ */
{
Wire.beginTransmission(1);
Wire.write(counter); /*......... to send count detail to them.*/
Wire.endTransmission();
digitalWrite(CNTSNT,HIGH);
digitalWrite(CNTSNT,LOW);
}
} /* The above loop for LDR 1 and 8 detection is completed. */
/* The same procedure is followed for detection of LDR 2 and 7*/
else if(ldr2>Lock&&ldr7<Lock)
{
ldr();
if(ldr8<Lock&&ldr7<Lock)
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
if(ldr9<Lock9)
{
ldr();
delay(665);
if((ldr7>Lock&&ldr2<Lock)&&(ldr8<Lock&&ldr1<Lock))
{
counter=counter+1;
EEPROM.write(8,counter);
}
else if((ldr7>Lock&&ldr2<Lock)&&((ldr8<Lock&&ldr1>Lock)||(ldr8>Lock&&ldr1<Lock)))
{
counter=counter+1;
EEPROM.write(8,counter);
continue;
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr1<Lock&&ldr8<Lock))
{
e2==1;
EEPROM.write(10,e2);
ldr27();
continue;
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr1>Lock&&ldr8<Lock))
{
e2==2;
EEPROM.write(10,e2);
ldr27();
continue;
}
else if((ldr2>Lock&&ldr7>Lock)&&(ldr8>Lock&&ldr1<Lock))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
}
else if(ldr9>Lock9&&ldr1>Lock)
{
delay(665);
if((ldr7>Lock&&ldr8>Lock)&&(ldr2<Lock&&ldr1<Lock))
{
if(Alerten==1)
{
counter=counter+1;
EEPROM.write(8,counter);
}
else
{
counter=counter+2;
EEPROM.write(8,counter);
}
}
}
else if(ldr9<Lock9&&ldr1>Lock)
{
e2==1;
EEPROM.write(10,e2);
e1==1;
EEPROM.write(9,e1);
while(e1==1&&e2==1)
{
compnx(&e8,&e7,&e1,&e2,&counter); 
}
}
else
{
}
if(ldr8<Lock&&ldr7<Lock)
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
}
/* If two persons crosses LDR 1 & 2 at the same time, then….. */
else if((ldr1>Lock&&ldr2>Lock)&&(ldr8<Lock&&ldr7<Lock))
{
if(ldr8<Lock&&ldr7<Lock)
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
ldr();
delay(655);
if(ldr9>Lock9&&ldr1>Lock&&ldr2>Lock&&ldr8>Lock&&ldr7>Lock) /* LDR 9 is placed between LDR 1, 2, 7 and 8 to prevent twice increment due to a passenger passing between LDR 1 and 2. Similarly LDR 10 is placed between LDR 3, 4, 5 and 6 to prevent double count for detection of both LDR 3 and 4 by one passenger. */
{
delay(665);
if((ldr8>Lock&&ldr7>Lock)&&(ldr1<Lock&&ldr2<Lock)) /* If LDR 8 & 7 detects darkness when 1,2 not detected then….... */
{ 
counter=counter+2; /* ...........count is incremented twice. */
EEPROM.write(8,counter);
}
else if((ldr8>Lock&&ldr7>Lock)&&(ldr1>Lock&&ldr2>Lock)) /* When all LDR’s
detected, then…… */
{
e1==1;
EEPROM.write(9,e1);
e2==1;
EEPROM.write(10,e2);
delay(665);
while(e1==1&&e2==1)
{
compnx(&e8,&e7,&e1,&e2,&counter);    /* compnx function is called. */
}
}
else
{
}
}
else if(ldr9<Lock9) /* If LDR 9 not detected after 665 milliseconds delay, then it indicates that only one passenger enters. */
{
 delay(665);
 if((ldr8>Lock&&ldr1<Lock)||(ldr7>Lock&&ldr2<Lock))
{
counter=counter+1;
EEPROM.write(8,counter);
continue;
}
else if((ldr8<Lock&&ldr1>Lock)||((ldr7<Lock&&ldr2>Lock))
{
 continue;
}
else if((ldr8>Lock&&ldr7>Lock)&&(ldr1>Lock&&ldr2>Lock)) /* If a passenger stands in between LDR 1, 2, 7 & 8............*/
{
ldr();
e1==1; 
EEPROM.write(9,e1);
e2==1;
EEPROM.write(10,e2);    /*.......then both e1 and e2 becomes 1 and calls ldr18() or ldr27() depending upon the passengers position. */
delay(665);
while(e1==1&&e2==1) 
{
if((ldr8>Lock&&ldr1<Lock)||(ldr7>Lock&&ldr2<Lock))
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0; 
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
continue;
}
else if((ldr8<Lock&&ldr1>Lock)||((ldr7<Lock&&ldr2>Lock))
{
e1==0; 
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
 continue;
}
else if ((ldr8>Lock&&ldr1>Lock)&&(ldr2<Lock&&ldr7<Lock)) 
{
e1==1; 
EEPROM.write(9,e1);
ldr18();
continue;   
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr2>Lock&&ldr7<Lock))  
{
e1==2;
EEPROM.write(9,e1);
ldr18();
continue;
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr7>Lock&&ldr2<Lock)) 
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr1<Lock&&ldr8<Lock))
{
e2==1;
EEPROM.write(10,e2);
ldr27();
continue;
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr1>Lock&&ldr8<Lock))
{
e2==2;
EEPROM.write(10,e2);
ldr27();
continue;
}
else if((ldr2>Lock&&ldr7>Lock)&&(ldr8>Lock&&ldr1<Lock))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
}
}
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
}
else
{
}
} /* So far the above loops increments the count either once or twice. */
else if(e1==1||e1==2)
{
ldr();
ldr18();
continue; 
}
else if(e2==1||e2==2)
{
ldr();
ldr27();
continue;
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr7>Lock&&ldr<Lock))
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
continue;
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr2>Lock&&ldr7<Lock))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
continue;
}
else if(e7==1||e7==2)
{
ldr();
ldr72();
continue;
}
else if(e8==1||e8==2)
{
ldr();
ldr81();
continue;
}
/* Now the following loops for once or twice count decrement. Transmission from LDR 8  or 7 to LDR 1 or 2  indicates that the passenger exits the train resulting in count decrement. */
else if((ldr8>Lock&&ldr7>Lock)&&(ldr1<Lock&&ldr2<Lock)) /* Twice decrement. */
{
if(ldr1<Lock&&ldr2<Lock)
{
Alertex==0;
EEPROM.write(11,Alertex);
}
else
{
Alertex==1;
EEPROM.write(11,Alertex);
}
ldr();
delay(665);
if(ldr9>Lock9&&ldr1>Lock&&ldr2>Lock&&ldr8>Lock&&ldr7>Lock)
{
ldr();
delay(665);
if((ldr1>Lock&&ldr2>Lock)&&(ldr8<Lock&&ldr7<Lock))
{
counter=counter-2;
EEPROM.write(8,counter);
}
else if((ldr1>Lock&&ldr2>Lock)&&(ldr8>Lock&&ldr7>Lock))
{
e8==1;
EEPROM.write(12,e8);
e7==1;
EEPROM.write(13,e7);
delay(665);
while(e8==1&&e7==1)
{
compnx(&e8,&e7,&e1,e2,&counter);
}
}
else
{
}
}
else if(ldr9<Lock9)
{
delay(665);
if((ldr1>Lock&&ldr8<Lock)||(ldr2>Lock&&ldr7<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
continue;
}
else if((ldr8>Lock&&ldr1<Lock)||(ldr7>Lock&&ldr2<Lock))
{
continue;
}
else if((ldr2>Lock&&ldr7>Lock)&&(ldr1>Lock&&ldr8>Lock))
{
ldr();
e8==1;
EEPROM.write(12,e8);
e7==1;
EEPROM.write(13,e7);
delay(665);
while(e8==1&&e7==1)
{
if((ldr1>Lock&&ldr8<Lock)||(ldr2>Lock&&ldr7<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
e7==0;
EEPROM.write(13,e7);
continue;
}
else if((ldr8>Lock&&ldr1<Lock)||(ldr7>Lock&&ldr2<Lock))
{
e8==0;
EEPROM.write(12,e8);
e7==0;
EEPROM.write(13,e7);
continue;
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr8<Lock&&ldr1<Lock))
{
e7==1;
EEPROM.write(11,e7);
ldr72();
continue;
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr8>Lock&&ldr1<Lock))
{
e7==2;
EEPROM.write(11,e7);
ldr72();
continue;
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr1>Lock&&ldr8<Lock))
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
else if((ldr1>Lock&&ldr8>Lock)&&(ldr7<Lock&&ldr2<Lock))
{
e8==1;
EEPROM.write(12,e8);
ldr81();
continue;
}
else if((ldr1>Lock&&ldr8>Lock)&&(ldr7>Lock&&ldr2<Lock))
{
e8==2;
EEPROM.write(12,e8);
ldr81();
continue;
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr2>Lock&&ldr7<Lock))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
}
}
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
if(ldr1<Lock&&ldr2<Lock)
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
/* Now two else if statements occurs for single count decrement by detection from LDR 7 to 2 or LDR 8 to 1. */
else if(ldr7>Lock&&ldr2<Lock)
{
if(ldr1<Lock&&ldr2<Lock)
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
ldr();
delay(655);
if(ldr9<Lock9) 
{
ldr();
delay(655);
if((ldr2>Lock&&ldr7<Lock)&&(ldr1<Lock&&ldr8<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((ldr2>Lock&&ldr7<Lock)&&((ldr1<Lock&&ldr8>Lock)||(ldr1>Lock&&ldr8<Lock)))
{
counter=counter-1;
EEPROM.write(8,counter);
continue;
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr8<Lock&&ldr1<Lock))
{
e7==1;
EEPROM.write(11,e7);
ldr72();
continue;
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr8>Lock&&ldr1<Lock))
{
e7==2;
EEPROM.write(11,e7);
ldr72();
continue;
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr1>Lock&&ldr8<Lock))
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
else
{
Alerten==1;
EEPROM.write(7,Alerten);
}
}
else if(ldr9>Lock9&&ldr8>Lock)
{
ldr();
delay(655);
if((ldr2>Lock&&ldr1>Lock)&&(ldr7<Lock&&ldr8<Lock))
{
if(Alertex==1)
{
counter=counter-1;
EEPROM.write(8,counter);
}
else
{
counter=counter-2;
EEPROM.write(8,counter);
}
}
}
else if(ldr9<Lock9&&ldr1>Lock)
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
else
{
}
if(ldr1<Lock&&ldr2<Lock)
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
else if((ldr8>Lock&&ldr1<Lock))
{
if(ldr1<Lock&&ldr2<Lock)
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
ldr();
delay(665);
if(ldr9<Lock9)
{
ldr();
delay(665);
if((ldr1>Lock&&ldr8<Lock)&&(ldr2<Lock&&ldr7<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if((ldr1>Lock&&ldr8<Lock)&&((ldr2<Lock&&ldr7>Lock)||(ldr2>Lock&&ldr7<Lock)))
{
counter=counter-1;
EEPROM.write(8,counter);
continue;
}
else if((ldr1>Lock&&ldr8>Lock)&&(ldr7<Lock&&ldr2<Lock))
{
e8==1;
EEPROM.write(12,e8);
ldr81();
continue;
}
else if((ldr1>Lock&&ldr8>Lock)&&(ldr7>Lock&&ldr2<Lock))
{
e8==1;
EEPROM.write(12,e8);
ldr81();
continue;
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr2>Lock&&ldr7<Lock))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
Alerten==1;
EEPROM.write(7,Alerten);
}
}
else if(ldr9>Lock9&&ldr7>Lock)
{
ldr();
delay(665);
if((ldr1>Lock&&ldr2>Lock)&&(ldr8<Lock&&ldr7<Lock))
{
if(Alertex==1)
{
counter=counter-1;
EEPROM.write(8,counter);
}
else
{
counter=counter-2;
EEPROM.write(8,counter);
}
}
}
else if(ldr9<Lock9&&ldr2>Lock)
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else
{
} 
if(ldr1<Lock&&ldr2<Lock)
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
void ldr18(). /* Function called when passenger stands between LDR 1 and 8 after entering halfway.*/
{
while(e1==1) 
{
ldr();
if((ldr8>Lock&&ldr1<Lock)&&(ldr7<Lock&&ldr2<Lock)).   /* count increases if enters completely............ */ 
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr7<Lock&&ldr2<Lock)) / *  .....or not if he / she exits. */
{
e1==0;
EEPROM.write(9,e1);
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr7<Lock&&ldr2>Lock))
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr7<Lock&&ldr2>Lock))
{
e1==0;
EEPROM.write(9,e1);
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr7>Lock&&ldr2<Lock))
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr7>Lock&&ldr2<Lock))
{
e1==0;
EEPROM.write(9,e1);
} 
else if(((ldr8>Lock&&ldr1>Lock)&&(ldr2>Lock&&ldr7<Lock))) /* If passenger still stands and another passenger boards..... */
{
e2==1;     /*...... then e2 becomes 1 and compnx function will determine. */
EEPROM.write(10,e2);
delay(665);
while(e1==1&&e2==1)
{
compnx(&e8,&e7,&e1,&e2,&counter);
}
}
else if(((ldr8>Lock&&ldr1>Lock)&&(ldr7>Lock&&ldr2<Lock)))  /* If another passenger exits, then nocount function is used. */
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
/* If the passenger who standard between ldr1 & 8 goes between 7 and 2 or towards 2 or towards 7 then..... */
else if((ldr1<Lock&&ldr8<Lock&&e1==1)&&(ldr7>Lock&&ldr2>Lock)) 
{
e1==0;
EEPROM.write(9,e1);
e2==1;
EEPROM.write(10,e2);
}
else if((ldr1<Lock&&ldr8<Lock&&e1==1)&&(ldr7>Lock&&ldr2<Lock)) 
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((ldr1<Lock&&ldr8<Lock&&e1==1)&&(ldr7<Lock&&ldr2>Lock)) 
{
e1==0;
EEPROM.write(9,e1);
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
while(e1==2) /* This e1 as 2 occurs when second passenger starts to board by crossing ldr2 */
{
ldr();
if((ldr8>Lock&&ldr1<Lock)&&((ldr2<Lock||ldr2>Lock)&&ldr7<Lock))
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if((ldr1>Lock&&ldr8<Lock)&&((ldr2<Lock||ldr2>Lock)&&ldr7<Lock))
{
e1==0;
EEPROM.write(9,e1);
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr2>Lock&&ldr7>Lock))  
{
counter=counter+1;
EEPROM.write(8,counter);
e2==1;
EEPROM.write(10,e2);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else if(((ldr1>Lock&&ldr8<Lock)&&(ldr2>Lock&&ldr7>Lock)))
{
e1==0;
EEPROM.write(9,e1);
e2==1;
EEPROM.write(10,e2);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else
if(((ldr1>Lock&&ldr8>Lock)&&(ldr2>Lock&&(ldr7>Lock||ldr7<Lock))))
{
e2==1;
EEPROM.write(10,e2);
delay(665);
while(e1==2&&e2==1) /* Here while loop will check whether any one gets zero. */
{
compnx(&e8,&e7,&e1,&e2,&counter);
}
if(e2==0). /* If e2 becomes zero, then e1 becomes 1 and checks whether passenger moves inside or outside or shifts between ldr 2 and 7. */
{
 e1==1;
EEPROM.write(9,e1);
}
}
else if((ldr8>Lock&&ldr7>Lock)&&(ldr1<Lock&&ldr2<Lock))
{
if(Alerten==0&&(ldr8>Lock&&e1==1)&&ldr1<Lock)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(Alerten==0&&(ldr7>Lock&&e2==1)&&ldr2<Lock)
{
counter=counter+2;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&(e1==1||e2==1))
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&e1==0&&e2==0)
{
counter=counter+2;
EEPROM.write(8,counter);
}
else if(Alerten==1&&e1==1)
{
counter=counter+1;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(Alerten==1&&e1==0)
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
}
/* Formal parameters nocount1() and nocount2() are used to avoid count if entering and exiting takes place simultaneously. */
void nocount1(int *p,int *s,int *count,int *ena,int *exa)
{
ldr();
if((ldr8>Lock&&ldr1<Lock)&&(ldr2>Lock&&ldr7<Lock))
{
*count=(*count)+0;
EEPROM.write(0,*count);
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr7>Lock&&ldr2<Lock))
{
*count=(*count)+1;
EEPROM.write(0,*count);
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr2>Lock&&ldr7>Lock))
{
*count=(*count)+1;
EEPROM.write(0,*count);
*s==1;
EEPROM.write(5,*s);
delay(665);
if(ldr2>Lock&&ldr7<Lock)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*s==0;
EEPROM.write(5,*s);
}
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr2>Lock&&ldr7<Lock))
{
*count=(*count)-1;
EEPROM.write(0,*count);
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr2>Lock&&ldr7<Lock))
{
*count=(*count)-1;
EEPROM.write(0,*count);
*p==1;
EEPROM.write(1,*p);
if(ldr8>Lock&&ldr1<Lock)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*p==0;
EEPROM.write(1,*p);
}
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr2>Lock&&ldr7>Lock))
{
*p==1;
EEPROM.write(1,*p);
*s==1;
EEPROM.write(5,*s);
if((ldr8>Lock&&ldr1<Lock)&&(ldr2>Lock&&ldr7<Lock))
{
*count=(*count)+0;
EEPROM.write(0,*count);
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr7>Lock&&ldr2<Lock))
{
*count=(*count)+1;
EEPROM.write(0,*count);
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr2>Lock&&ldr7>Lock))
{
*count=(*count)+1;
EEPROM.write(0,*count);
*s==1;
EEPROM.write(5,*s);
delay(665);
if(ldr2>Lock&&ldr7<Lock)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*s==0;
EEPROM.write(5,*s);
}
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr2>Lock&&ldr7<Lock))
{
*count=(*count)-1;
EEPROM.write(0,*count);
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr2>Lock&&ldr7<Lock))
{
*count=(*count)-1;
EEPROM.write(0,*count);
*p==1;
EEPROM.write(1,*p);
if(ldr8>Lock&&ldr1<Lock)
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
if(ldr8<Lock&&ldr7<Lock)
{
*ena==0;
EEPROM.write(5,*ena);
}
else
{
*ena==1;
EEPROM.write(5,*ena);
}
if(ldr1<Lock&&ldr2<Lock)
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
void ldr27()
{
while(e2==1)
{
ldr();
if((ldr7>Lock&&ldr2<Lock)&&(ldr8<Lock&&ldr1<Lock))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((ldr2>Lock&&ldr7<Lock)&&(ldr8<Lock&&ldr1<Lock))
{
e2==0;
EEPROM.write(10,e2);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr8<Lock&&ldr1>Lock))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((ldr2>Lock&&ldr7<Lock)&&(ldr8<Lock&&ldr1>Lock))
{
e2==0;
EEPROM.write(10,e2);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr8>Lock&&ldr1>Lock))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((ldr2>Lock&&ldr7<Lock)&&(ldr8>Lock&&ldr1<Lock))
{
e2==0;
EEPROM.write(10,e2);
}
else if((ldr2>Lock&&ldr7>Lock)&&(ldr8<Lock&&ldr1>Lock))
{
e1==1;
EEPROM.write(9,e1);
delay(665);
while(e2==1&&e1==1)
{
compnx(&e8,&e7,&e1,&e2,&counter);
}
}
else if((ldr2>Lock&&ldr7>Lock)&&(ldr8>Lock&&ldr1<Lock))
{
nocount2(&e2,&e8,&counter,&Alerten,&Alertex);
}
else if((ldr2<Lock&&ldr7<Lock&&e2==1)&&(ldr8>Lock&&ldr1>Lock))
{
e2==0;
EEPROM.write(10,e2);
e1==1;
EEPROM.write(9,e1);
}
else if((ldr2<Lock&&ldr7<Lock&&e2==1)&&(ldr8>Lock&&ldr1<Lock))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((ldr2<Lock&&ldr7<Lock&&e2==1)&&(ldr8<Lock&&ldr1>Lock))
{
e2==0;
EEPROM.write(10,e2);
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
while(e2==2)
{
ldr();
if((ldr7>Lock&&ldr2<Lock)&&(ldr8<Lock&&(ldr1>Lock||ldr1<Lock)))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if((ldr2>Lock&&ldr7<Lock)&&(ldr8<Lock&&(ldr1>Lock||ldr1<Lock)))
{
e2==0;
EEPROM.write(10,e2);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr8>Lock&&ldr1>Lock))
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
e1==1;
EEPROM.write(9,e1);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr8>Lock&&ldr1>Lock))
{
e2==0;
EEPROM.write(10,e2);
e1==1;
EEPROM.write(9,e1);
compnx(&e8,&e7,&e1,&e2,&counter);
}
else if((ldr2>Lock&&ldr7>Lock)&&(ldr8>Lock&&(ldr1>Lock||ldr1<Lock)))
{
e1==1;
EEPROM.write(9,e1);
delay(665);
while(e2==2&&e1==1)
{
compnx(&e8,&e7,&e1,&e2,&counter);
}
if(e1==0)
{
e2==1;
EEPROM.write(10,e2);
}
}
else if((ldr7>Lock&&ldr8>Lock)&&(ldr2<Lock&&ldr1<Lock))
{
if(Alerten==0&&(ldr8>Lock&e1==1)&&ldr1<Lock)
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
}
else if(Alerten==0&&(ldr7>Lock&e2==1)&&ldr2<Lock)
{
counter=counter+2;
EEPROM.write(0,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&(e1==1||e2==1))
{
counter=counter+2;
EEPROM.write(8,counter);
e1==0;
EEPROM.write(9,e1);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==0&&e1==0&&e2==0)
{
counter=counter+2;
EEPROM.write(8,counter);
}
else if(Alerten==1&&e2==1)
{
counter=counter+1;
EEPROM.write(8,counter);
e2==0;
EEPROM.write(10,e2);
}
else if(Alerten==1&&e2==0)
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
}
void compnx(int *r, int *s, int *p, int*q, int *count) /* This function is called when the passenger stands below the LDR sensor for the long time without entering or exiting. */
{
ldr();
if(ldr8>Lock&&((*p)==1||(*p)==2)&&ldr1<Lock)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*p==0;
EEPROM.write(1,*p);
delay(665);
if(ldr7>Lock&&((*q)==1||(*q)==2)&&ldr2<Lock)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*q==0;
EEPROM.write(2,*q);
}
else if(ldr2>Lock&&((*q)==1||(*q)==2)&&ldr7<Lock)
{
*q==0;
EEPROM.write(2,*q);
}
else
{
}
}
else if(ldr1>Lock&&((*p)==1||(*p)==2)&&ldr8<Lock)
{
*p==0;
EEPROM.write(1,*p);
delay(665);
if(ldr7>Lock&&((*q)==1||(*q)==2)&&ldr2<Lock)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*q==0;
EEPROM.write(2,*q);
}
else if(ldr2>Lock&&((*q)==1||(*q)==2)&&ldr7<Lock)
{
*q==0;
EEPROM.write(2,*q);
}
else
{
}
}
else if(ldr7>Lock&&((*q)==1||(*q)==2)&&ldr2<Lock)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*q==0;
EEPROM.write(2,*q);
delay(665);
if(ldr8>Lock&&((*p)==1||(*p)==2)&&ldr1<Lock)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*p==0;
EEPROM.write(1,*p);
}
else if(ldr1>Lock&&((*p)==1||(*p)==2)&&ldr8<Lock)
{
*p==0;
EEPROM.write(1,*p);
}
else
{
}
}
else if(ldr2>Lock&&((*q)==1||(*q)==2)&&ldr7<Lock)
{
*q==0;
EEPROM.write(2,*q);
delay(665);
if(ldr8>Lock&&((*p)==1||(*p)==2)&&ldr1<Lock)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*p==0;
EEPROM.write(1,*p);
}
else if(ldr1>Lock&&((*p)==1||(*p)==2)&&ldr8<Lock)
{
*p==0;
EEPROM.write(1,*p);
}
else
{
}
}
else
if(((ldr8>Lock&&((*p)==1||(*p)==2))&&(ldr7>Lock&&((*q)==1||(*q)==2
)))&&(ldr1<Lock&&ldr2<Lock))
{
*count=(*count)+2;
EEPROM.write(0,*count);
*p==0;
EEPROM.write(1,*p);
*q==0;
EEPROM.write(2,*q);
}
else
if(((ldr1>Lock&&((*r)==1||(*r)==2))&&(ldr2>Lock&&((*s)==1||(*s)==2)))&&(ldr8<Lock&&ldr7<Lock))
{
*count=(*count)-2;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
*s==0;
EEPROM.write(5,*s);
}
else if(ldr2>Lock&&((*s)==1||(*s)==2)&&ldr7<Lock)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*s==0;
EEPROM.write(5,*s);
if(ldr1>Lock&&((*r)==1||(*r)==2)&&ldr8<Lock)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
}
else if(ldr8>Lock&&((*r)==1||(*r)==2)&&ldr1<Lock)
{
*r==0;
EEPROM.write(4,*r);
}
else
{
}
}
else if(ldr7>Lock&&((*s)==1||(*s)==2)&&ldr2<Lock)
{
*s==0;
EEPROM.write(5,*s);
if(ldr1>Lock&&((*r)==1||(*r)==2)&&ldr8<Lock)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
}
else if(ldr8>Lock&&((*r)==1||(*r)==2)&&ldr1<Lock)
{
*r==0;
EEPROM.write(4,*r);
}
else
{
}
}
else if(ldr1>Lock&&((*r)==1||(*r)==2)&&ldr8<Lock)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
if(ldr2>Lock&&((*s)==1||(*s)==2)&&ldr7<Lock)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*s==0;
EEPROM.write(5,*s);
}
else if(ldr7>Lock&&((*s)==1||(*s)==2)&&ldr2<Lock)
{
*s==0;
EEPROM.write(5,*s);
}
else
{
}
}
else if(ldr8>Lock&&((*r)==1||(*r)==2)&&ldr1<Lock)
{
*r==0;
EEPROM.write(4,*r);
if(ldr2>Lock&&((*s)==1||(*s)==2)&&ldr7<Lock)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*s==0;
EEPROM.write(5,*s);
}
else if(ldr7>Lock&&((*s)==1||(*s)==2)&&ldr2<Lock)
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
void ldr72()
{
while(e7==1)
{
if((ldr2>Lock&&ldr7<Lock)&&(ldr1<Lock&&ldr8<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr1<Lock&&ldr8<Lock))
{
e7==0;
EEPROM.write(11,e7);
}
else if((ldr2>Lock&&ldr7<Lock)&&(ldr8>Lock&&ldr1<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr8>Lock&&ldr1<Lock))
{
e7==0;
EEPROM.write(11,e7);
}
else if((ldr2>Lock&&ldr7<Lock)&&(ldr1>Lock&&ldr8<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==1;
EEPROM.write(12,e8);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr1>Lock&&ldr8<Lock))
{
e7==0;
EEPROM.write(8,e7);
e8==1;
EEPROM.write(12,e8);
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr8>Lock&&ldr1<Lock))
{
e8==1;
EEPROM.write(12,e8);
delay(665);
while(e7==1&&e8==1)
{
compnx(&e8,&e7,&e1,e2,&counter);
}
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr1>Lock&&ldr8<Lock))
{
nocount1(&e1,&e7,&counter,&Alerten,&Alertex);
}
else if((ldr7>Lock&&ldr2>Lock&&e7==1)&&(ldr8>Lock&&ldr1>Lock))
{
e7==0;
EEPROM.write(8,e7);
e8==1;
EEPROM.write(12,e8);
}
else if((ldr7>Lock&&ldr2>Lock&&e7==1)&&(ldr1>Lock&&ldr8<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(8,e7);
}
else if((ldr7>Lock&&ldr2>Lock&&e7==1)&&(ldr8>Lock&&ldr1<Lock))
{
e7==0;
EEPROM.write(8,e7);
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
while(e7==2)
{
if((ldr2>Lock&&ldr7<Lock)&&(ldr1<Lock&&ldr8<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr1<Lock&&ldr8<Lock))
{
e7==0;
EEPROM.write(11,e7);
}
else if((ldr2>Lock&&ldr7<Lock)&&(ldr8>Lock&&ldr1<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr8>Lock&&ldr1<Lock))
{
e7==0;
EEPROM.write(11,e7);
}
else if((ldr2>Lock&&ldr7<Lock)&&(ldr1>Lock&&ldr8>Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(11,e7);
e8==1;
EEPROM.write(12,e8);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr8>Lock&&ldr1>Lock))
{
e7==0;
EEPROM.write(8,e7);
e8==1;
EEPROM.write(12,e8);
compnx(&e8,&e7,&e1,e2,&counter);
}
else
if((ldr7>Lock&&ldr2>Lock)&&(ldr8>Lock&&(ldr1>Lock||ldr1<Lock)))
{
e8==1;
EEPROM.write(12,e8);
delay(665);
while(e7==2&&e8==1)
{
compnx(&e8,&e7,&e1,e2,&counter);
}
if(e8==0)
{
e7==1;
EEPROM.write(8,e7);
}
}
else if((ldr2>Lock&&ldr1>Lock)&&(ldr7<Lock&&ldr8<Lock))
{
if(Alertex==0&&ldr2>Lock&&e7==1&&ldr7<Lock)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==0&&ldr1>Lock&&e8==1&&ldr8<Lock)
{
counter=counter-2;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&(e8==1||e7==1))
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&e8==0&&e7==0)
{
counter=counter-2;
EEPROM.write(8,counter);
}
else if(Alertex==1&&e7==1)
{
counter=counter-1;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==1)
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
}
void nocount2(int *q,int *r,int *count,int *ena,int *exa)
{
ldr();
if((ldr7>Lock&&ldr2<Lock)&&(ldr1>Lock&&ldr8<Lock))
{
*count=(*count)+0;
EEPROM.write(0,*count);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr1<Lock&&ldr8>Lock))
{
*count=(*count)+1;
EEPROM.write(0,*count);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr1>Lock&&ldr8>Lock))
{
*count=(*count)+1;
EEPROM.write(0,*count);
*r==1;
EEPROM.write(4,*r);
if(ldr1>Lock&&ldr8<Lock)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
}
}
else if((ldr7<Lock&&ldr2>Lock)&&(ldr1>Lock&&ldr8<Lock))
{
*count=(*count)-1;
EEPROM.write(0,*count);
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr1>Lock&&ldr8<Lock))
{
*count=(*count)-1;
EEPROM.write(0,*count);
*q==1;
EEPROM.write(2,*q);
if(ldr7>Lock&&ldr2<Lock)
{
*count=(*count)+1;
EEPROM.write(0,*count);
*q==0;
EEPROM.write(2,*q);
}
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr2>Lock&&ldr7>Lock))
{
*r==1;
EEPROM.write(4,*r);
*q==1;
EEPROM.write(2,*q);
if((ldr7>Lock&&ldr2<Lock)&&(ldr1>Lock&&ldr8<Lock))
{
*count=(*count)+0;
EEPROM.write(0,*count);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr1<Lock&&ldr8>Lock))
{
*count=(*count)+1;
EEPROM.write(0,*count);
}
else if((ldr7>Lock&&ldr2<Lock)&&(ldr1>Lock&&ldr8>Lock))
{
*count=(*count)+1;
EEPROM.write(0,*count);
*r==1;
EEPROM.write(4,*r);
if(ldr1>Lock&&ldr8<Lock)
{
*count=(*count)-1;
EEPROM.write(0,*count);
*r==0;
EEPROM.write(4,*r);
}
}
else if((ldr7<Lock&&ldr2>Lock)&&(ldr1>Lock&&ldr8<Lock))
{
*count=(*count)-1;
EEPROM.write(0,*count);
}
else if((ldr7>Lock&&ldr2>Lock)&&(ldr1>Lock&&ldr8<Lock))
{
*count=(*count)-1;
EEPROM.write(0,*count);
*q==1;
EEPROM.write(2,*q);
if(ldr7>Lock&&ldr2<Lock)
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
if(ldr8<Lock&&ldr7<Lock)
{
*ena==0;
EEPROM.write(3,*ena);
}
else
{
*ena==1;
EEPROM.write(3,*ena);
}
if(ldr1<Lock&&ldr2<Lock)
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
void ldr81()
{
while(e8==1)
{
if((ldr1>Lock&&ldr8<Lock)&&(ldr2<Lock&&ldr7<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr2<Lock&&ldr7<Lock))
{
e8==0;
EEPROM.write(12,e8);
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr2<Lock&&ldr7>Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr2<Lock&&ldr7>Lock))
{
e8==0;
EEPROM.write(12,e8);
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr7>Lock&&ldr2<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr7>Lock&&ldr2<Lock))
{
e8==0;
EEPROM.write(12,e8);
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr7>Lock&&ldr2<Lock))
{
e7==1;
EEPROM.write(13,e7);
delay(665);
while(e8==1&&e7==1)
{
compnx(&e8,&e7,&e1,e2,&counter);
}
}
else if((ldr8>Lock&&ldr1>Lock&&e8==1)&&(ldr7>Lock&&ldr2>Lock))
{
e8==0;
EEPROM.write(12,e8);
e7==1;
EEPROM.write(13,e7);
}
else if((ldr8>Lock&&ldr1>Lock&&e8==1)&&(ldr2>Lock&&ldr7<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((ldr8>Lock&&ldr1>Lock&&e8==1)&&(ldr7>Lock&&ldr2<Lock))
{
e8==0;
EEPROM.write(12,e8);
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr2>Lock&&ldr7<Lock))
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
while(e8==2)
{
if((ldr1>Lock&&ldr8<Lock)&&(ldr2<Lock&&ldr7<Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr2<Lock&&ldr7<Lock))
{
e8==0;
EEPROM.write(12,e8);
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr2<Lock&&ldr7>Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if((ldr8>Lock&&ldr1<Lock)&&(ldr2<Lock&&ldr7>Lock))
{
e8==0;
EEPROM.write(12,e8);
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr7>Lock&&ldr2>Lock))
{
counter=counter-1;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
e7==1;
EEPROM.write(13,e7);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((ldr1>Lock&&ldr8<Lock)&&(ldr7>Lock&&ldr2>Lock))
{
e8==0;
EEPROM.write(12,e8);
e7==1;
EEPROM.write(13,e7);
compnx(&e8,&e7,&e1,e2,&counter);
}
else if((ldr8>Lock&&ldr1>Lock)&&(ldr7>Lock&&ldr2<Lock))
{
e7==1;
EEPROM.write(13,e7);
delay(665);
while(e8==2&&e7==1)
{
compnx(&e8,&e7,&e1,e2,&counter);
}
if(e7==1)
{
e8==1;
EEPROM.write(12,e8);
}
}
else if((ldr1>Lock&&ldr2>Lock)&&(ldr8<Lock&&ldr7<Lock))
{
if(Alertex==0&&(ldr2>Lock&&e7==1)&&ldr7<Lock)
{
counter=counter-2;
EEPROM.write(8,counter);
e7==0;
EEPROM.write(13,e7);
}
else if(Alertex==0&&(ldr1>Lock&&e8==1)&&ldr8<Lock)
{
counter=counter-2;
EEPROM.write(8,counter);
e8==0;
EEPROM.write(12,e8);
}
else if(Alertex==0&&e7==0&&e8==0)
{
counter=counter-2;
EEPROM.write(8,counter);
}
else if(Alertex==1)
{
counter=counter-1;
EEPROM.write(8,counter);
}
else if(Alertex==1&&e8==1)
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
}
