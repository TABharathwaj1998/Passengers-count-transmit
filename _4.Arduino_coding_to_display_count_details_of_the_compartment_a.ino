                       /* Arduino coding to display count details of the compartment at station */
#include<EEPROM.h>
#include<Wire.h>
#include "SevSeg.h" /* This is the header file for calling Seven segment display library functions. */
SevSeg sevseg;
#define PIR1 22
#define PIR2 23
static int x1=0,count=0,stscount=0;
void setup()
{
Wire.begin(1);
pinMode(PIR1,INPUT);
pinMode(PIR2,INPUT);
byte numDigits = 4; /* Number of pins. */
byte digitPins[] = {10,11,12,13}; /* Pin numbers on which this display is connected. */
byte segmentPins[] = {2,3,4,5,6,7,8,9};
byte hardwareConfig= COMMON_CATHODE;
bool resistorOnSegments=true;
sevseg.begin(COMMON_CATHODE,numDigits,digitPins,segmentPins);
sevseg.setBrightness(100);
x1=EEPROM.read(0);
stscount=EEPROM.read(1);
count=EEPROM.read(2);
}
void loop()
{
x1=Wire.read(); /* Receives coach 1 details of upcoming train. */
EEPROM.write(0,x1);
/* Counting of passengers using PIR sensor and storing at “stscount" meaning Station count. */
if(digitalRead(PIR1)==1&&digitalRead(PIR2)==0)
{
delay(1330);
if(digitalRead(PIR2)==1&&digitalRead(PIR1)==0)
{
stscount=(stscount+1)*10;
EEPROM.write(1,stscount);
}
}
else if(digitalRead(PIR2)==1&&digitalRead(PIR1)==0)
{
delay(1330);
if(digitalRead(PIR1)==1&&digitalRead(PIR2)==0)
{
stscount=(stscount-1)*10;
EEPROM.write(1,stscount);
}
}
/* If no counting happens, then “stscount" and x1 which are three digit number are multiplied with 10 and then……… */
else
{
if(0<=x1<=25)
{
count= stscount +(x1*10)+1; /* added with 1 to indicate vacant compartment. */
}
else if(26<=x1<=130)
{
count= stscount +(x1*10)+2; /* added with 2 indicating less crowded compartment */
}
else if(131<=x1<=145)
{
count= stscount +(x1*10)+3; /* added with 3 indicating moderate crowd */
}
else if(x1>=146)
{
count= stscount +(x1*10)+4; /* added with 4 indicating most crowded compartment */
}
else if(x1==3909)
{
count==x1; /* Error value which occurs when 1st compartment needs maintenance. */
}
else
{
}
EEPROM.write(2,count);
sevseg.setNumber(count,1); /* 1 indicates decimal point after 1st digit from R.H.S. For instance when count is 1353 then this
function will make this number as 135.3 which means moderate crowd. */
sevseg.refreshDisplay();
}
}
/* The above coding is repeated for all the 12 displays present at station. */
