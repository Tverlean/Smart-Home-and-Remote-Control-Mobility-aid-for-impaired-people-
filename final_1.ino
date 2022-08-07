//Conditions:
//FOR FAN:
    //When the up button on the remote is pressed, the dc motor works.
  //When the down button on the remote is pressed, the dc motor will stop on working
//FOR WINDOW 1:
//When number "1" press on the remote,
  //the servo motors for Window 1 place on 0 degrees, 
  //and "Window 1 Close" will appear on the LCD together with the "Windows Status."
//when number "2" press on the remote, 
  //the servo motor for Window 1 place on 180 degrees, 
  //and "Window 1 Open" will appear on the LCD together with the "Windows Status."
//FOR WINDOW 2:
//when number "3" press on the remote, 
  //the servo motor for Window 2 place on 0 degrees, 
  //and "Window 2 Close" will appear on the LCD together with the "Windows Status."
//when number "4" press on the remote, 
  //the servo motor for Window 2 place on 180 degrees, 
  //and "Window 2 Open" will appear on the LCD together with the "Windows Status."
//FOR PIR:
  //When the PIR value is "1", the servomotors for door will rotate 180 degree.
  //When the PIR value is "0", nothings happen with the servomotors for door.
//FOR PHOTORESISTOR:
//When the intensity of light is very low
  //the bulb lights up
//When the intensity of light is high
  //the bulb turns off
#include<Servo.h>
#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32, 16, 2);
int IRpin=3;
IRrecv IR(IRpin);
int relayPin=8,readPin=A3;
int t=1500;
int pirPin=4;
int pirVal;
int pirPin2=12;
int motorPin=7;
int dcMotor=11;
int switchState=0;

int servoPina=5,servoPina1=6,servoPinb=2;
Servo servoA;
Servo servoA1;
Servo servoB;
float angleVala,angleValb;
unsigned long fromStartms; //millis from start
unsigned long prevms; //millis previous read
unsigned long interval=1000;

void setup()
{
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
Serial.begin(9600);
pinMode(IRpin,INPUT);
IR.enableIRIn();
pinMode(pirPin,INPUT);
pinMode(pirPin2,INPUT);
pinMode(motorPin,OUTPUT);
pinMode(dcMotor,OUTPUT);
pinMode(relayPin,OUTPUT);
pinMode(readPin,INPUT);
pinMode(servoPina,OUTPUT);
servoA.attach(servoPina);
pinMode(servoPina1,OUTPUT);
servoA1.attach(servoPina1);
  
pinMode(servoPinb,OUTPUT);
servoB.attach(servoPinb);
Serial.begin(9600);
}

void loop()   
{
  

 //for Automatic Door 
{
fromStartms=millis();
pirVal=digitalRead(pirPin);
if(fromStartms - prevms >= interval)
{
prevms = fromStartms;
    
if(pirVal==1)
{
  servoB.write(180);
  }
  else
  {
  servoB.write(0);
  }
  Serial.println(pirVal);
 { 
//for LDR(photoresistor)
int readVal= analogRead(readPin);
delay(t);

if (readVal>500)
{
digitalWrite(relayPin,LOW);
}
else
{
  digitalWrite(relayPin,HIGH);
//For Remote Controlling Windows and LCD.  
lcd.setCursor(0,0);
lcd.print("Status:");
while(IR.decode())
{

  if(IR.decodedIRData.decodedRawData==0xFF00BF00)
  {
   Serial.println("POWER");
   lcd.clear();
  }
  if(IR.decodedIRData.decodedRawData==0xF50ABF00)//SWITCH ON FAN
  {
   Serial.println("UP");
   digitalWrite(dcMotor,HIGH);
   lcd.setCursor(0,0);
   lcd.print("Status:");
   lcd.setCursor(0,1);
   lcd.print("Fan turns On");
  }
   if(IR.decodedIRData.decodedRawData==0xF708BF00)//SWITCH OFF FAN
  {
   Serial.println("DOWN");
   digitalWrite(dcMotor,LOW);
   lcd.setCursor(0,0);
   lcd.print("Status:");
   lcd.setCursor(0,1);
   lcd.print("Fan turns off");
  }
  if(IR.decodedIRData.decodedRawData==0xEF10BF00)
  {
   Serial.println(1);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Status:");
   lcd.setCursor(0,1);
   lcd.print("Window 1 Close");
   servoA.write(0);
  }
  if(IR.decodedIRData.decodedRawData==0xEE11BF00)
  {
   Serial.println(2);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Status:");
   lcd.setCursor(0,1);
   lcd.print("Window 1 Open");
   servoA.write(180);
  }
  if(IR.decodedIRData.decodedRawData==0xED12BF00)
  {
   Serial.println(3);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Status:");
   lcd.setCursor(0,1);
   lcd.print("Window 2 Close");
   servoA1.write(0);
  }
  if(IR.decodedIRData.decodedRawData==0xEB14BF00)
  {
   Serial.println(4);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Status:");
   lcd.setCursor(0,1);
   lcd.print("Window 2 Open");
   servoA1.write(180);
  }
IR.resume();
}
}
}
}
}
}
  
