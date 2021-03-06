float temp;
int tempsensor = 0;
#define PIR 2
#define BUTTON 7
#define FAN 4
#define Clk 9
#define AntiClk 10
void setup() 
{
 pinMode(PIR,INPUT);
 pinMode(BUTTON,INPUT);
 pinMode(FAN,OUTPUT);
 pinMode(Clk,OUTPUT);
 pinMode(AntiClk,OUTPUT);
 Serial.begin(9600);
}
void loop()
{
 static int p=0,b=0;
 int detect,button;
 temp=analogRead(tempsensor);
 temp=temp*0.48828125;              
 temp=temp/10;
 detect=digitalRead(PIR);
 button=digitalRead(BUTTON);
 Serial.print(temp);
 Serial.print("'C\n");
 delay(1000); 
 if((detect)==1&&(b==0))
 {
  if(p==0)
  {
   p=p+1;
   Serial.print("Person Enters the room\n");       //Consider the scenario where the room space is suitable for only one person. If more than one, then coding will be changed where if(p==0) will be changed to if(p>=0).
   delay(1000);
  }
  else
  {
   p=p*0;
   Serial.print("Person Exits the room\n");
   delay(1000); 
  }
  if(b==0)
  {
   Serial.print("Fan is in OFF condition\n");
   delay(1000); 
  }
 }
 if((button==0)&&(p==1))
 {
  if(b==0)
  {
   b=b+1;
   Serial.print("Fan is in ON condition\n");
   delay(1000);
   if(button==0)
   {
    b=b*1;
   }
  }
  else
  {
   b=b*0;
   digitalWrite(FAN,LOW);
   Serial.print("Fan is in OFF condition\n");
   delay(1000); 
  }
 }
 if((temp<3.00)&&(p==1)&&(b==1))
 {
  digitalWrite(FAN,LOW);
 }
 else if((3.20>temp>=3.00)&&(p==1)&&(b==1))
 {
  digitalWrite(FAN,HIGH);
  analogWrite(Clk,127);
  analogWrite(AntiClk,0);
  Serial.print("24'C\n");
  delay(1000);
  if((detect)==1&&((p==1)))
  {
   p=p*0;
   b=b*0;
   digitalWrite(FAN,LOW);
   Serial.print("Person exits the room\n");
   delay(1000); 
  }
  if((button==0)&&(p==1)&&(b==1))
  {
   b=b*1;  
  } 
 }
 else if((temp>=3.20)&&(temp<3.40)&&(p==1)&&(b==1))
 {
  digitalWrite(FAN,HIGH);
  analogWrite(Clk,191);
  analogWrite(AntiClk,0);
  Serial.print("22'C\n");
  delay(1000);
  if((detect)&&(p==1))
  {
   p=p*0;
   b=b*0;
   digitalWrite(FAN,LOW);
   Serial.print("Person exits the room\n");
   delay(1000);
  }
  if((button==0)&&(p==1)&&(b==1))
  {
   b=b*1;  
  } 
 }
 else if((temp>=3.40)&&(p==1)&&(b==1))
 {
  digitalWrite(FAN,HIGH);
  analogWrite(Clk,255);
  analogWrite(AntiClk,0);
  Serial.print("20'C\n");
  delay(1000);
  if((detect==1)&&(p==1))
  { 
   p=p*0;
   b=b*0;
   digitalWrite(FAN,LOW);
   Serial.print("Person exits the room\n");
   delay(1000);
  }
  if((button==0)&&(p==1)&&(b==1))
  {
   b=b*1;
  }   
 }
 else 
 {
  
 }
 Serial.print(p);
 Serial.print("\n");
 Serial.print(b);
 Serial.print("\n");
 delay(1000);
}
