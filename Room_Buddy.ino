#include<SoftwareSerial.h>
#include <Servo.h>
#include <TM1637Display.h>
// Define the connections pins:
#define CLK 12
#define DIO 13
// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(CLK, DIO);
Servo myservo_1;
Servo myservo_2;
SoftwareSerial myserial(A4,A5); // RX,TX
float cel;
int b=3;
int x=0;
int flag=0;
int UP=11;
int DOWN=10;
int ledPin = 13;                // LED 
int pirPin = 2;                 // PIR Out pin 
int ldrPin=A0;
int tempPin=A1;
int windPin=A2;
float ac_temp=25;
float temp(){
  int val = analogRead(tempPin);
   cel = ( val/1024.0)*500;
  //float cel=mv/10;
  //Serial.println(cel);
  return cel;
}

int pir(){
  int pirStat=digitalRead(pirPin); 
 if (pirStat == HIGH) {            // if motion detected
   flag=1;
 } 
 else {
   flag=0;
 }
 return flag;
}

void ldr(int f){
  if (f==1){
    int y=analogRead(A0);
    y=map(y,0,200,0,400);
    if (y>=0 and y<100){
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);}
    else if(y>=100 and y<200){
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);}
    else if(y=200 and y<300){
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);}
    else{
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW); } 
   }
  else{
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
   }
}

float wind(){
  float windSpeed;
  int sensorValue = analogRead(windPin); //Get a value between 0 and 1023 from the analog pin connected to the anemometer
  float sensorVoltage = sensorValue * 0.004882814; //Convert sensor value to actual voltage
  if (sensorVoltage <= 0.4){
  windSpeed = 0; //Check if voltage is below minimum value. If so, set wind speed to zero.
  }else {
  windSpeed = (sensorVoltage - 0.4)*32/(2.0 - 0.4); //For voltages above minimum value, use the linear relationship to calculate wind speed.
  }
  return windSpeed;
}
void w_close(){
digitalWrite(9,HIGH);
delay(620);
digitalWrite(9,LOW);
delay(220);
x=0;
b=3;
}
void w_open(){
digitalWrite(8,HIGH);
delay(620);
digitalWrite(8,LOW);
delay(220);
x=1;
b=0;
}
void window(float n,float m,float l){

  if(n>15){
    if(abs(m-l)<=5){
      if(x==0)
        w_open();
       
    }
    else
    {
      if(x==1){
        w_close();}
     
    }}
   
}


void setup() {
 display.clear();
 pinMode(7,OUTPUT);
 pinMode(6,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(11,INPUT);
 pinMode(10,INPUT);
 pinMode(tempPin,INPUT);
 pinMode(A0,INPUT);
 pinMode(ledPin, OUTPUT);     
 pinMode(pirPin, INPUT);     
 Serial.begin(9600);
}
void loop(){
  ldr(pir());
  window(16,25,ac_temp);
  if(digitalRead(10)==HIGH)
    b=0;
  if(digitalRead(11)==HIGH)
    b=3;
//if(digitalRead(UP)==HIGH)
  //ac_temp++;
//else if(digitalRead(DOWN)==HIGH)
  //ac_temp--;
if(b==3)
  display.setBrightness(3);
display.showNumberDec(ac_temp);

}

  
  
 
