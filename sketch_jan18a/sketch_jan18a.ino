//code values
#include <IRremote.h>
IRsend irsend;

const int inputPin = 2;  //pin for pullup resistor
int value = 0;
int ledLaser =  13;         //pin for laser led  
int pressurewarning = 7;
int pgmcontrol = 5;
int lastvalue = 0;     // previous state of the button

//decode
//counter to begin the game
int count = 0;
//Receptor
int points = 0;
const int analogInPin = A0;

const int analogInPin1 = A6;
const int analogInPin2 = A7;
int sensorValue = 0;        // value read from the push button
int sensorValue2 = 0;       // value read from pressure sensor

int LaserValue = 0;
int PointC = 1;//By this pin we will send the data to the OLED display for points

void setup() {  
  pinMode(ledLaser, OUTPUT);  //Set pin 13 as output
  pinMode(pressurewarning, OUTPUT);
  pinMode(pgmcontrol, OUTPUT);
  Serial.begin(9600);      //Start serial communication  
  pinMode(PointC, OUTPUT);  //Set pin 11 as output
}

void loop(){     
  value = digitalRead(inputPin);  //read the digital input
  PullUp(); 
  LaserValue = analogRead(analogInPin);

  sensorValue = analogRead(analogInPin1);
  sensorValue2 = analogRead(analogInPin2);
  
  delay(10);
//  Serial.print(LaserValue);
//  Serial.print("\n");
  Points();
}
//Encode
void PullUp(){       
  if (value != lastvalue) {
    if (value == HIGH) {
        SendPluse(); //I call the function pulse
        Serial.println("Hello world");
        delay(10);
    }
  }   
  lastvalue = value;//Evaluate the last state of the push buttom 
}

void SendPluse(){ 
  //We will send 1 pulse
  digitalWrite(ledLaser, HIGH);
  delay(1000);
  
  if (sensorValue2>250){
    digitalWrite(pgmcontrol, HIGH);
    delay(500);
    digitalWrite(pgmcontrol,LOW);
    digitalWrite(pressurewarning,LOW);
    }
    else {
    digitalWrite(pgmcontrol, LOW);
    digitalWrite(pressurewarning,HIGH);
    delay(500);
    digitalWrite(pressurewarning,LOW);    
    }
  irsend.sendSony(0x68B90, 20);
  digitalWrite(ledLaser, LOW); 

  digitalWrite(pgmcontrol,LOW);
  }


//decode
void Points() {
  if(LaserValue > 180) {
    digitalWrite(PointC, HIGH);
    delay(1000);
    digitalWrite(PointC, LOW);  
  }  
  LaserValue = 0;

}
