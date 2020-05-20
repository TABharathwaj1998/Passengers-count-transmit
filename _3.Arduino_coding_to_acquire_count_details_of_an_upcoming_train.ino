                 /* Arduino coding to acquire count details of an upcoming train */
#include<Wire.h>  /* Wire library for I2C data transfer. */
#include<SoftwareSerial.h> /* Wire library for HC-12 data transfer */
SoftwareSerial HC12(10,11); /* 10-TXD, 11-RXD. */
#include<EEPROM.h>
int priority();
int passengerscount(int details);
int snr1=0;
int snr2=1;
int snr3=2;
int snr4=3;
int snr=4;
int ltn1=5;
int ltn2=6;
int TD1,TD2,TD3,TD4,TD,LT1,LT2;
long int x,y,tno,counter,Tno,details;
static int z=0,p=0,c=0;
static int P121,P112,P103,P94,P85,P76,P67,P58,P49,P310,P211,P1P12;
static int indicate=0,Sts=0,Status=0,Error=0,Confirmed=0,Fix=0,d=0,Check=0,transmit=0,rcve=0,receive=0,Step=0,coach1=0,send=0,S=0,time=0,Alert=0;
int e=3909;
#define T1 22
#define T2 23
#define T3 24
#define T4 25
#define TCOMP1 26
#define TCOMP2 27
#define TCOMP3 28
#define TCOMP4 29
#define TCOMP5 30
#define TCOMP6 31
#define TCOMP7 32
#define TCOMP8 33
#define LSRSND1 34
#define LSRSND2 36
#define LSRRCVE2 37
#define ALRTOUT 38
#define ALRTIN 39
void setup() 
{
 HC12.begin(9600);
 Wire.begin();
 pinMode(T1,OUTPUT);
 pinMode(T2,OUTPUT);
 pinMode(T3,OUTPUT);
 pinMode(T4,OUTPUT);
 pinMode(TCOMP1,OUTPUT);
 pinMode(TCOMP2,OUTPUT);
 pinMode(TCOMP3,OUTPUT);
 pinMode(TCOMP4,OUTPUT);
 pinMode(TCOMP5,OUTPUT);
 pinMode(TCOMP6,OUTPUT);
 pinMode(TCOMP7,OUTPUT);
 pinMode(TCOMP8,OUTPUT);
 pinMode(LSRSND1,OUTPUT);
 pinMode(LSRSND2,OUTPUT);
 pinMode(LSRRCVE2,INPUT);
 pinMode(ALRTOUT,OUTPUT);
 pinMode(ALRTIN,INPUT);
Alert=EEPROM.read(0);
x=EEPROM.read(1);
Tno=EEPROM.read(2);
Fix=EEPROM.read(3);
d=EEPROM.read(4);
counter=EEPROM.read(5);
z=EEPROM.read(6);
p=EEPROM.read(7);
Confirmed=EEPROM.read(8);
Error=EEPROM.read(9);
Check=EEPROM.read(10);
y=EEPROM.read(11);
P121=EEPROM.read(12);
P112=EEPROM.read(13);
P103=EEPROM.read(14);
P94=EEPROM.read(15);
P85=EEPROM.read(16);
P76=EEPROM.read(17);
P67=EEPROM.read(18);
P58=EEPROM.read(19);
P49=EEPROM.read(20);
P310=EEPROM.read(21);
P211=EEPROM.read(22);
P1P12=EEPROM.read(23);
indicate=EEPROM.read(24);
Sts=EEPROM.read(25);
Status=EEPROM.read(26);
Step=EEPROM.read(29);
send=EEPROM.read(29);
time=EEPROM.read(30);
S=EEPROM.read(31);
}
int priority()
{
  P121==1;
  EEPROM.write(12,P121);
  P112==1;
  EEPROM.write(13,P112);
  P103==1;
  EEPROM.write(14,P103);
  P94==1;
  EEPROM.write(15,P94);
  P85==1;
  EEPROM.write(16,P85);
  P76==1;
  EEPROM.write(17,P76);
 P67==1;
 EEPROM.write(18,P67); 
 P58==1;
 EEPROM.write(19,P58); 
 P49==1;
 EEPROM.write(20,P49);
 P310==1;
 EEPROM.write(21,P310);
 P211==1;
 EEPROM.write(22,P211);
 P1P12==1;
 EEPROM.write(23,P1P12);
}
int passengerscount(int details)   
{                                        
  details=details*0;
  EEPROM.write(0,details);
  Wire.beginTransmission(1);
  Wire.write(details);
  Wire.endTransmission();
  Wire.beginTransmission(2);
  Wire.write(details);
  Wire.endTransmission();
  Wire.beginTransmission(3);
  Wire.write(details);
  Wire.endTransmission();
  Wire.beginTransmission(4);
  Wire.write(details);
  Wire.endTransmission();
  Wire.beginTransmission(5);
  Wire.write(details);
  Wire.endTransmission();
  Wire.beginTransmission(6);
  Wire.write(details);
  Wire.endTransmission();
  Wire.beginTransmission(7);
  Wire.write(details);
  Wire.endTransmission();
  Wire.beginTransmission(8);
  Wire.write(details);
  Wire.endTransmission();
  Wire.beginTransmission(9);
  Wire.write(details);
  Wire.endTransmission();
  Wire.beginTransmission(10);
  Wire.write(details);
  Wire.endTransmission();
  Wire.beginTransmission(11);
  Wire.write(details);
  Wire.endTransmission();
  Wire.beginTransmission(12);
  Wire.write(details);
  Wire.endTransmission();
  return details; 
}
void loop() 
{
 if(HC12.available()&&Step!=2)  /* By this condition…... */                   
 {
   x=HC12.read(); /* ....x receives HC12 value indicating upcoming train information. */
   EEPROM.write(1,x);
  if(Fix==0&&(01301001000<=x<=9925412999))
   {
    Tno=x*(10^-8);     /* Under Fix=0, train number is extracted and checked whether odd or even. */
    EEPROM.write(2,Tno);
    digitalWrite(ALRTOUT,HIGH); /* Then this station sends an Alert signal to an Arduino which then...... */
   if(digitalRead(ALRTIN)==1) /* .....sends signal so that....... */
    {
        Alert==1;    
        EEPROM.write(0,Alert);
        Wire.beginTransmission(13);
        Wire.write(x);  /* ...... This Arduino sends upcoming train details to that Arduino. */
        Wire.endTransmission();       
    }
    if(Tno%2==1) 
   {
     x=(10^8)+(x-(Tno*(10^8)));    /* 1st digit from L.H.S is 1 if odd and other digits has other details. */
     EEPROM.write(1,x);
   }
   else if(Tno%2==0)
   {
     x=(2*(10^8))+(x-(Tno*(10^8)));     /* 1st digit is 2 if even. */
     EEPROM.write(1,x);
   }
   else
   {
   }
   Fix==1; /* Fix becomes 1 so that train number will be received by d from x. */
   EEPROM.write(3,Fix);
  }
  else if((Fix==1||Fix==0)&&(01301111<=x<=9925414))  /* This is the Status of Arrival / Departure of the upcoming train*/
  {  
   Tno=x*(10^-5);
   EEPROM.write(2,Tno); 
   if(Tno%2==1) 
   {
     x=(10^5)+(x-(Tno*(10^5)));
     EEPROM.write(1,x);
     Sts==x; 
     EEPROM.write(25,Sts); 

   }
   else if(Tno%2==0)
   {
     x=(2*(10^5))+(x-(Tno*(10^5))); 
     EEPROM.write(1,x);
     Sts==x; 
     EEPROM.write(25,Sts);
   }
   else
   {
   }       
  }
  else if(Fix==1&&(01301101000<=x<=9925412999))
  {
    d=x*(10^-8);    /* Extraction is done only when this variable is equal to Tno. */
    EEPROM.write(4,d);   
    digitalWrite(ALRTOUT,HIGH); 
    if(digitalRead(ALRTIN)==1)
    {
        Alert==1;
        EEPROM.write(0,Alert);
        Wire.beginTransmission(13);
        Wire.write(x);
        Wire.endTransmission();       
    }     
    if(d%2==1) 
   {
     x=(10^8)+(x-(d*(10^8)));    
     EEPROM.write(1,x);
   }
   else if(d%2==0)
   {
     x=(2*(10^8))+(x-(d*(10^8)));     
     EEPROM.write(1,x);
   }
   else
   {
   }
  }
  else
  {
    
  }
  /* The train count details is collected by the following loops….. */
  if((104100000<=x<=104112999)&&d==Tno) /* ….first loop..... */ 
 {
   counter=(x-104100000);   /* Extracts train number 1. */ 
   EEPROM.write(5,counter);
   z==4;                        
   EEPROM.write(6,z);
   p==1;
   EEPROM.write(7,p);
   if(Alert==1)
   {
    Confirmed==0;      
    EEPROM.write(8,Confirmed);        
   }
   else
   {
    Confirmed==1;      
    EEPROM.write(8,Confirmed);
   }
 }
 else if(210100000<=x<=210112999&&d==Tno) /* Second loop..... */
 {
   counter=(x-211100000);   /* .....Extracts train number 2. */
   EEPROM.write(5,counter);
   z==10;
   EEPROM.write(6,z);
   p==1;
   EEPROM.write(7,p);
   if(Alert==1)
   {
    Confirmed==0;      
    EEPROM.write(8,Confirmed);        
   }
   else
   {
    Confirmed==1;      
    EEPROM.write(8,Confirmed);
   }
 }
 else if((104300000<=x<=104312999)&&d==Tno)  /* if 4th digit from LHS contains 3, it indicates power interruption with next compartment which does not receives details from this compartment that sends x value to the station. */ 
 {
   counter=(x-104300000); 
   EEPROM.write(5,counter);
   z==4;                        
   EEPROM.write(6,z);
   if(Confirmed==1) /* If train number is confirmed, then Error and Alert becomes 0. */
   {
    p==3;
    EEPROM.write(7,p);  
    Error==0;
    EEPROM.write(9,Error);   
    Alert==0;
    EEPROM.write(0,Alert);     
   }
   else
   {      
    p==3;
    EEPROM.write(7,p);
    Alert==1;
    EEPROM.write(0,Alert);
   }
 }
 else if(210300000<=x<=210312999&&d==Tno)
 {
   counter=(x-211300000);
   EEPROM.write(5,counter);
   z==10;
   EEPROM.write(6,z);
   if(Confirmed==1)
   {
    p==3;
    EEPROM.write(7,p);   
    Error==0;
    EEPROM.write(9,Error);   
    Alert==0;
    EEPROM.write(0,Alert);    
   }
   else
   {      
    p==3;
    EEPROM.write(7,p);
    Alert==1;
    EEPROM.write(0,Alert);
   }
 }
 else if((104400000<=x<=104412999)&&d==Tno) /*  4th digit as 4 indicates error similar to 3 as digit if Platform is 2. */
 {
   counter=(x-104400000);    
   EEPROM.write(5,counter);
   z==4;                        
   EEPROM.write(6,z);
   if(Confirmed==1)
   {
    p==2;
    EEPROM.write(7,p);      
    Error==0;
    EEPROM.write(9,Error);   
    Alert==0;
    EEPROM.write(0,Alert);  
   }
   else
   {      
    p==4;
    EEPROM.write(7,p);
    Alert==1;
    EEPROM.write(0,Alert);
   }
}
 else if(210400000<=x<=210412999&&d==Tno)   
 {
   counter=(x-211400000);        
   EEPROM.write(5,counter);
   z==10;
   EEPROM.write(6,z);
   if(Confirmed==1)
   {
    p==2;
    EEPROM.write(7,p);      
    Error==0;
    EEPROM.write(9,Error);  
    Alert==0;
    EEPROM.write(0,Alert);   
   }
   else
   {      
    p==4;
    EEPROM.write(7,p);
    Alert==1;
    EEPROM.write(0,Alert);
   }
 }
 else if(((100100000<x<=104100999)||(104112999<x<=104300999)||(210100000<x<=210100999)||(210112999<x<=210300999))&&d==Tno) /* If the upcoming train sends a wrong station code……... */
 {
   Check=x*(10^-5);  /* ………Check variable extracts Train number……….*/
   EEPROM.write(10,Check);
   counter=x-(Check*(10^5));    /* …….and subtracted with x containing upcoming train details. */
   EEPROM.write(5,counter);
   if(Alert==1)
   {
    Confirmed==0;      
    EEPROM.write(8,Confirmed);        
   }
   else
   {
    Confirmed==1;      
    EEPROM.write(8,Confirmed);
   }
   if((Tno%2)==1)
   {
     z==4;
     EEPROM.write(6,z);
     p==1;
     EEPROM.write(7,p);
     Error==1;
     EEPROM.write(9,Error);
   }
   else if((Tno%2)==0)
   {
     z==10;
     EEPROM.write(6,z);
     p==1;
     EEPROM.write(7,p);
     Error==1;
     EEPROM.write(9,Error);
   }
   else
   {
                
   }
   Check==0;
   EEPROM.write(10,Check);
 }
 else if(((100300000<x<=104300999)||(104312999<x<=210300999)||(210312999<x))&&d==Tno) /* Same condition but the platform number is 3. */
 {
   Check=x*(10^-5);
   EEPROM.write(10,Check);
   counter=x-(Check*(10^5));
   EEPROM.write(5,counter);
   if(Alert==1)
   {
    Confirmed==0;      
    EEPROM.write(8,Confirmed);        
   }
   else
   {
    Confirmed==1;      
    EEPROM.write(8,Confirmed);
   }
   if((Tno%2)==1)
   {
     z==4;
     EEPROM.write(6,z);
     p==3;
     EEPROM.write(7,p);
     Error==1;
     EEPROM.write(9,Error);
   }
   else if((Tno%2)==0)
   {
     z==10;
     EEPROM.write(6,z);
     p==3;
     EEPROM.write(7,p);
     Error==1;
     EEPROM.write(9,Error);
   }
   else
   {
                
   }
   Check==0;
   EEPROM.write(10,Check);
  }
  else if(d!=Tno) /* If not equal, then Arduino will....... */
  {
   digitalWrite(ALRTOUT,HIGH); /* ..... send to Arduino that acquires this detail, checks whether train is present at the station checked by train number and sends to that platform */
  /* Train detail which was extracted will be merged again and sent. */  if(digitalRead(ALRTIN)==1&&(100000000<=x<=199999999))
   {
    Wire.beginTransmission(13);
    Wire.write((d*10^8)+(x-100000000));
    Wire.endTransmission();       
   }  
   else if(digitalRead(ALRTIN)==1&&(200000000<=x<=299999999))
   {
    Wire.beginTransmission(13);
    Wire.write((d*10^8)+(x-200000000));
    Wire.endTransmission();       
   }   
   else
   {
                
   }          
  }
  else
  {
  }    
 if(((1000<counter<1999)&&(P121==1))) /* This is the details of the first compartment. */                 
 {
  if(Error==1) /* If Error is 1, then Arduino at station sends correct station code to the train compartment. */
  {
    x=(Tno*10000)+(z*100)+(p*10)+1;
    EEPROM.write(1,x);
    HC12.write(x);
  }
  else
  {
  P121==0;                            
     /* This indicates priority which is needed so that the compartment details which are transmitted already should not be repeated again and again leaving the other compartment details which would have been unable to transmit due to environmental conditions or communication interferences. */
  EEPROM.write(12,P121);
  y=counter-1000;
  EEPROM.write(11,y);
  Wire.beginTransmission(1);       
  Wire.write(y);                                     
   Wire.endTransmission();                    
 }
} 
 else if((2000<y<2999)&&(P112==1))  /* Second compartment. */
 {
   if(Error==1)
  {
    x=(Tno*10000)+(z*100)+(p*10)+2;
    EEPROM.write(1,x);
    HC12.write(x);
  }
  else
  {
  P112==0;
  EEPROM.write(13,P112);
  y=counter-2000;
  EEPROM.write(11,y);  
  Wire.beginTransmission(2);
  Wire.write(y);                                         
  Wire.endTransmission();  
 }   
}
else if((3000<y<3999)&&(P103==1))  /* Third */
{
    if(Error==1)
  {
    x=(Tno*10000)+(z*100)+(p*10)+3;
    EEPROM.write(1,x);
    HC12.write(x);
  }
 else
 {
   P103==0;
   EEPROM.write(14,P103);
   y=counter-3000;
   EEPROM.write(11,y);
   Wire.beginTransmission(3);
   Wire.write(y);
   Wire.endTransmission();    
  }      
 }
 else if((4000<y<4999)&&(P94==1))     /* Fourth */
 {
     if(Error==1)
  {
    x=(Tno*10000)+(z*100)+(p*10)+4;
    EEPROM.write(1,x);
    HC12.write(x);
  }
  else
  {
   P94==0;
   EEPROM.write(15,P94);
   y=counter-4000;
   EEPROM.write(11,y);

   Wire.beginTransmission(4);
   Wire.write(y);
   Wire.endTransmission();    
  }       
 }
 else if((5000<y<5999)&&(P85==1))       /* Fifth */
 {
   if(Error==1)
  {
    x=(Tno*10000)+(z*100)+(p*10)+5;
    EEPROM.write(1,x);
    HC12.write(x);
  }
   else
  {
   P85==0;
   EEPROM.write(16,P85);
   y=counter-5000;
   EEPROM.write(11,y);  
   Wire.beginTransmission(5);       
   Wire.write(y);
   Wire.endTransmission();    
  }       
 }
 else if((6000<y<6999)&&(P76==1))      /* Sixth */
 {
    if(Error==1)
  {
    x=(Tno*10000)+(z*100)+(p*10)+6;
    EEPROM.write(1,x);
    HC12.write(x);
  }
  else
  {
   P76==0;
   EEPROM.write(17,P76);
   y=counter-6000;
   EEPROM.write(11,y);
   Wire.beginTransmission(6);       
   Wire.write(y);                                       
   Wire.endTransmission();       
  }    
 }
 else if((7000<counter<7999)&&(P67==1))     /* Seventh */
 {
  if(Error==1)
  {
    x=(Tno*10000)+(z*100)+(p*10)+7;
    EEPROM.write(1,x);
    HC12.write(x);
  }
   else
  {
    P67==0;
    EEPROM.write(18,P67);
    y=counter-7000;
    EEPROM.write(11,y);
    Wire.beginTransmission(7);       
    Wire.write(y);                                               
    Wire.endTransmission(); 
  }          
 }
 else if((8000<y<8999)&&(P58==1))     /* Eighth */
 {
  if(Error==1)
  {
    x=(Tno*10000)+(z*100)+(p*10)+8;
    EEPROM.write(1,x);
    HC12.write(x);
  }
  else
  {         
  P58==0;
  EEPROM.write(19,P58);
  y=counter-8000;
  EEPROM.write(11,y);  
  Wire.beginTransmission(8);       
  Wire.write(y);                                                
  Wire.endTransmission();    
  }      
 }
 else if((9000<y<9999)&&(P49==1))       /* Ninth */
 {
    if(Error==1)
  {
    x=(Tno*10000)+(z*100)+(p*10)+9;
    EEPROM.write(1,x);
    HC12.write(x);
  }
  else
  {
   P49==0;
   EEPROM.write(20,P49);
   y=counter-9000;
   EEPROM.write(11,y);
   Wire.beginTransmission(9);       
   Wire.write(y);                                               
   Wire.endTransmission();
  }           
 }
 else if((10000<y<10999)&&(P310==1))        /* Tenth */
 {
   if(Error==1)
  {
    x=(Tno*10000)+(z*100)+(p*10)+10;
    EEPROM.write(1,x);
    HC12.write(x);
  }    
  else 
  {
   P310==0;
   EEPROM.write(21,P310);
   y=counter-10000;
   EEPROM.write(11,y);
   Wire.beginTransmission(10);       
   Wire.write(y);                                               
   Wire.endTransmission();    
  }      
 }
 else if((11000<y<11999)&&(P211==1))      /* Eleventh */
 {
   if(Error==1)
  {
    x=(Tno*10000)+(z*100)+(p*10)+11;
    EEPROM.write(1,x);
    HC12.write(x);
  }
  else
  {
   P211==0;
   EEPROM.write(22,P211);
   y=counter-11000;
   EEPROM.write(11,y);
   Wire.beginTransmission(11);       
   Wire.write(y);                                               
   Wire.endTransmission(); 
  }          
 }
 else if((12000<y<12999)&&(P1P12==1))    /* Twelve */
 {
  if(Error==1)
  {
    x=(Tno*10000)+(z*100)+(p*10)+12;
    EEPROM.write(1,x);
    HC12.write(x);
  }
  else
  {
   P1P12==0;
   EEPROM.write(23,P1P12);
   y=counter-12000;
   EEPROM.write(11,y);         
  }          
 }
 else
 {
 }
 /* After extraction, it checks Sts value that is received from x value at initial stage of program. */
 if(Sts==104111||Sts==211111||Sts==104311||Sts==211311) /* When all the values as last digit 1, it indicates Arrival shown by A which is 1st letter. */
  {
   Status=1;   /* Status value becomes 1. */
   EEPROM.write(26,Status);
  }
  else if(Sts==104114||Sts==211114||Sts==104314||Sts==211314)
  {
   Status=4;   /* Status value becomes 4 if Sts has 4 the last digit. */
   EEPROM.write(26,Status);
  }
  else
  {
  }
 if(P121==0&&P112==0&& P103==0&& P94==0&& P85==0&& P76==0&& P67==0&& P58==0&& P49==0&& P310==0&& P211==0&& P1P12==0) 
 /* If priority of all compartments becomes 0, then all priority value becomes 1 by this function priority() and continues so on. */
 {
  indicate==1;   /* This variable will indicate the station that the train will arrive. */
  EEPROM.write(24,indicate);
  priority();           
 }
 else
 {
/* If any Priority value remains 1 even though the train has arrived as shown by Status value 1, then Arduino at station sends e= 3909 to Arduino which displays the error compartment. 3909 indicates Error as shown by inverting 3 to get E letter.*/     
        if((P121==1||P112==1||P103==1||P94==1||P85==1||P76==1||P67==1||P58==1||P49==1||P310==1||P211==1||P1P12==1)||(Status==1))
   {        
   if(P121==1)
   {
    Wire.beginTransmission(1);       
    Wire.write(e);                                                
    Wire.endTransmission(); 
    Alert==1; /* Alert becomes 1 so that Light detector will receive the train details for Confirmation. */
    EEPROM.write(0,Alert);                      
   }
   if(P112==1)
   {
    Wire.beginTransmission(2);       
    Wire.write(e);                                         
    Wire.endTransmission(); 
    Alert==1; 
    EEPROM.write(0,Alert);                      
   }
   if(P103==1)
   {
    Wire.beginTransmission(3);       
    Wire.write(e);                                         
    Wire.endTransmission(); 
    Alert==1; 
    EEPROM.write(0,Alert);                      
   }
   if(P94==1)
   {
    Wire.beginTransmission(4);         
    Wire.write(e);                                         
    Wire.endTransmission(); 
    Alert==1; 
    EEPROM.write(0,Alert);                      
   }
   if(P85==1)
   {
    Wire.beginTransmission(5);       
    Wire.write(e);                                         
    Wire.endTransmission(); 
    Alert==1; 
    EEPROM.write(0,Alert);                      
   }   
   if(P76==1)
   {
    Wire.beginTransmission(6);       
    Wire.write(e);                                         
    Wire.endTransmission(); 
    Alert==1; 
    EEPROM.write(0,Alert);                      
   }
   if(P67==1)
   {
    Wire.beginTransmission(7);       
    Wire.write(e);                                         
    Wire.endTransmission(); 
    Alert==1; 
    EEPROM.write(0,Alert);                      
   }
   if(P58==1)
   {
    Wire.beginTransmission(8);      
    Wire.write(e);                                         
    Wire.endTransmission(); 
    Alert==1; 
    EEPROM.write(0,Alert);                      
   }
   if(P49==1)
   {
    Wire.beginTransmission(9);       
    Wire.write(e);                                         
    Wire.endTransmission(); 
    Alert==1; 
    EEPROM.write(0,Alert);                      
   }   
   if(P310==1)
   {
    Wire.beginTransmission(10);          
    Wire.write(e);                                         
    Wire.endTransmission(); 
    Alert==1; 
    EEPROM.write(0,Alert);                      
   }
   if(P211==1)
   {
    Wire.beginTransmission(11);       
    Wire.write(e);                                         
    Wire.endTransmission(); 
    Alert==1; 
    EEPROM.write(0,Alert);                      
   }
   if(P1P12==1)
   {
    Wire.beginTransmission(12);         
    Wire.write(e);                                         
    Wire.endTransmission(); 
    Alert==1; 
    EEPROM.write(0,Alert);                      
   }             
   indicate==1;  
   EEPROM.write(24,indicate);
  }
 } 
 }                    
 if(indicate==1)
 {
  /* All the lights TCOMP 1 to 8 will switch ON if light intensity gets lower. */
  TD1=analogRead(snr1);
  TD2=analogRead(snr2);
  TD3=analogRead(snr3);
  TD4=analogRead(snr4);
  TD=analogRead(snr);
  LT1=analogRead(ltn1);
  LT2=analogRead(ltn2);
  if(TD<10&&Status==1) /* Then the station checks whether LDR (TD) placed in between the platform track has value less than 10 and Status value is 1 indicating that the train arrived so that Laser from station sends light once to 1st compartment to receive the Train number during Step 1. At Step 2 it transmits to the last compartment so that other compartments which are not able to receive the details from the 1st compartment will acquire details from the last compartment. */
  {
   if(Step==1&&(Alert==1||Error==1))
   {
     digitalWrite(LSRSND1,HIGH);
     delay(50);
     digitalWrite(LSRSND1,LOW);
     delay(50);
     if((700<LT1<800)&&(700<=LT2<=705)) /* Numbers from 0 to 99 is extracted and numbers from 0 to 5 is extracted. */
     { 
      Tno=((LT2-700)*100)+(LT1-700); /* Added to get Train number and making Confirmed value as 1. */
      EEPROM.write(2,Tno);
      Error==0;
      EEPROM.write(9,Error);
      Alert==0;
      EEPROM.write(0,Alert);
      Confirmed==1;
      EEPROM.write(8,Confirmed);
      Step==2;      
      EEPROM.write(28,Step);                                               
     }
     digitalWrite(ALRTOUT,HIGH);           
     if(digitalRead(ALRTIN)==1)
     {
      Wire.beginTransmission(13);
      Wire.write(Tno);
      Wire.endTransmission();       
     }                  
    }  
/* With the train number, it sends to the last compartment using Laser communication. */              
if(Step==2&&(Check==0||Check==1)) /* Check value becomes zero after extraction of train number if station code received from the upcoming train is wrong. */
{                                           
while(send<=Tno&&(digitalRead(LSRRCVE2)==1||digitalRead(LSRRCVE2)==0)&&S==0&&Check==0)
  {
   digitalWrite(LSRSND2,HIGH);
   delay(50);
   digitalWrite(LSRSND2,LOW);  
   delay(50);
   if(digitalRead(LSRRCVE2)==1)
   {
     send++;
     EEPROM.write(29,send);
     if(send==Tno)
     {
      digitalWrite(LSRSND2,HIGH);
      delay(50);
      digitalWrite(LSRSND2,LOW);
      delay(50);
      digitalWrite(LSRSND2,HIGH);
      delay(50);
      digitalWrite(LSRSND2,LOW);
      Error==0;
      EEPROM.write(9,Error);
      time=time*0;
      EEPROM.write(30,time);
      if(digitalRead(LSRRCVE2)==1)
      {
        delay(50);
        if(digitalRead(LSRRCVE2)==1)
       {
        Check==1;
        EEPROM.write(10,Check);
      }
     }
    }
   }
   else
   {
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
       EEPROM.write(30,time);
       if(time==1000)
       {
        Error==1;
        EEPROM.write(9,Error);
       }   
      }                                                    
     }                       
    }
   }   
   while((digitalRead(LSRRCVE2)==0||digitalRead(LSRRCVE2)==1)&&S>0&&Check==0)
   {
     digitalWrite(LSRSND2,HIGH);
     delay(50);
     digitalWrite(LSRSND2,LOW);
     delay(50);
     if(digitalRead(LSRRCVE2)==1)
     {
       S--;
       EEPROM.write(31,S);
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
         EEPROM.write(10,Check);
        } 
       }
      }
     } 
    else
    {
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
       EEPROM.write(30,time);
       if(time==1000)
       {
        Error==1;
        EEPROM.write(9,Error);
   
       }   
      }                                                    
     }                       
    }                   
   }
   while(Check==0&&send==Tno)   
   {
    delay(50);                  
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
         EEPROM.write(10,Check);
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
        EEPROM.write(10,Check);
       } 
      }                           
     }
    } 
    else
    {
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
           EEPROM.write(10,Check);
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
          EEPROM.write(10,Check);
         } 
        }                           
       }                        
      }
      else
      {                                                   
       time++;
       EEPROM.write(30,time);
       if(time==1000)
       {
        Error==1;
        EEPROM.write(9,Error);
       }   
      }                                                    
     }                       
    } 
   } 
   while(Check==1&&send>0)                                                                                                                                                                                           while(Check==1&&send>0)
   {
   delay(50);                      
   if(digitalRead(LSRRCVE2)==1)
   {
    delay(50);                      
    if(digitalRead(LSRRCVE2)==1)
    {
     delay(50);                      
     if(digitalRead(LSRRCVE2)==1)
     {
      send=send-1;
      EEPROM.write(29,send);
      if(send==0)
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
       delay(50);
       if(digitalRead(LSRRCVE2)==1)
       {
        Check==0;
        EEPROM.write(10,Check);
        Step==1;
       EEPROM.write(28,Step);
        priority(); 
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
        digitalWrite(LSRSND2,HIGH);
        delay(50);
        digitalWrite(LSRSND2,LOW);
        delay(50);                      
        if(digitalRead(LSRRCVE2)==1)
        {
         delay(50);                      
         if(digitalRead(LSRRCVE2)==1)
         {
          S=send*1;                                          
          EEPROM.write(31,S);                                 
          Check==0;
          EEPROM.write(10,Check);
         }  
        }
       }
       Error==0;
       EEPROM.write(9,Error);
       time=time*0;
       EEPROM.write(30,time);
      }
     }                               
     else
     {
      if(send==0)
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
       delay(50);
       if(digitalRead(LSRRCVE2)==1)
       {
        Check==0;
        EEPROM.write(10,Check);
        Step==1;
       EEPROM.write(28,Step);
        priority();
       }  
      }
      else
      {
       digitalWrite(LSRSND2,HIGH);
       delay(50);
       digitalWrite(LSRSND2,LOW);
       delay(50);  
       if(digitalRead(LSRRCVE2)==1)
       {
         S=(send*1)-1;                                          
         EEPROM.write(31,S);                                 
         Check==0;
         EEPROM.write(10,Check);
       }                                                                
      }                             
     }                                   
    }
    else
    {
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
       EEPROM.write(30,time);
       if(time==1000)
       {
        Error==1;
        EEPROM.write(9,Error);
       }   
      }                                                    
     }                            
    }                                      
   }
  } 
  else if(digitalRead(LSRRCVE2)==1&&Error==1&&Step==2)
  {

  }
  else
  {
  }     
   if(TD1<750)  
  {
   digitalWrite(TCOMP1,HIGH);
   digitalWrite(TCOMP2,HIGH);
  }
  if(TD2<750) 
  {
   digitalWrite(TCOMP3,HIGH);
   digitalWrite(TCOMP4,HIGH);
  } 
  if(TD3<750)  
  {
   digitalWrite(TCOMP5,HIGH);
   digitalWrite(TCOMP6,HIGH);
  }
  if(TD4<750)  
  {
   digitalWrite(TCOMP7,HIGH);
   digitalWrite(TCOMP8,HIGH);
  }   
/* "z" means station code for forward journey. After the train departs, it sends "Sts" value with last digit as 4 indicating Departure where D is the 4th letter. Then it crosses first over TD3 sensor and then TD4. After crossing both, train details are erased and all the values such as Status, Alert, Confirm, r and indicate values becomes zero. */  
if((z==4||r==1)&&TD3<10&&Status==4)    
 {
   digitalWrite(T3,HIGH); 
   if(TD4<10)
   {
     digitalWrite(T4,LOW);
     passengerscount(y);             
     priority();
   }
   if(TD3>10&&TD4>10&&Status==4)
   {           
    z=z*0;                                  
    EEPROM.write(6,z);
    r=r*0;
    EEPROM.write(27,r);
    Status=Status*0;
    EEPROM.write(26,Status);
    Sts==x*0;
    EEPROM.write(25,Sts);
    indicate=indicate*0;
    EEPROM.write(24,indicate);
    Error==0;
    EEPROM.write(9,Error);
    Confirmed==0;
    EEPROM.write(8,Confirmed);
    Tno==0;
    EEPROM.write(2,Tno);
    d==0;
    EEPROM.write(d,4);
    Alert==0;
    EEPROM.write(0,Alert);
  }
 }
 else if((z==11||r==1)&&TD2<10&&Status==4)   /* This loop is like previous loop which is used for return journey as shown by z=11. */
 {
   digitalWrite(T2,HIGH);
   if(TD1<10)
   {
     digitalWrite(T1,LOW);
     passengerscount(y);
     priority();
   }
  if(TD1>10&&TD2>10&&Status==4)
  {
   z=z*0;                                  
    EEPROM.write(6,z);
    r=r*0;
    EEPROM.write(27,r);
    Status=Status*0;
    EEPROM.write(26,Status);
    Sts==x*0;
    EEPROM.write(25,Sts);
    indicate=indicate*0;
    EEPROM.write(24,indicate);
    Error==0;
    EEPROM.write(9,Error);
    Confirmed==0;
    EEPROM.write(8,Confirmed);
    Tno==0;
    EEPROM.write(2,Tno);
    d==0;
    EEPROM.write(d,4);
    Alert==0;
   EEPROM.write(0,Alert);            
  }
 }
 else if(z==4&&TD2<10&&TD1>10) // Before arriving at station, the train moves over TD2 and TD1. After moving at both sensors, high intensity will make return 'r' value as zero so that if that train will make its return journey, then this r value will be useful. 
 {
   digitalWrite(T2,HIGH);
   digitalWrite(T1,LOW);
   if(TD1>10&&TD2>10&&Status==1)
  {
     r==1;
     EEPROM.write(27,r);
  }
 }
 else if(z==11&&TD4<10&&TD3>10)  /*  Same followed for return journey trains which may go towards previous station in case of track maintenance. */
 {
  digitalWrite(T4,HIGH);
  digitalWrite(T3,LOW); 
  if(TD3>10&&TD4>10&&Status==1)
  {
     r==1;
     EEPROM.write(27,r);
  }
 }       
 else
 {
   if(TD1>10&&TD2>10&& TD3>10&&TD4>10&&(Status==4||TD>10))
  {
    z=z*0;                                  
    EEPROM.write(6,z);
    r=r*0;
    EEPROM.write(27,r);
    Status=Status*0;
    EEPROM.write(26,Status);
    Sts==x*0;
    EEPROM.write(25,Sts);
    indicate=indicate*0;
    EEPROM.write(24,indicate);
    Error==0;
    EEPROM.write(9,Error);
    Confirmed==0;
    EEPROM.write(8,Confirmed);
    Tno==0;
    EEPROM.write(2,Tno);
    d==0;
    EEPROM.write(d,4);
    Alert==0;
   EEPROM.write(0,Alert); 
    }
   }
  }
 }
}
