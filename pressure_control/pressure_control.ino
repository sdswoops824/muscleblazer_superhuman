/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.
 // channel one on top two on bottom

 */

// These constants won't change.  They're used to give names
// to the pins used:

const int analogInPin1 = A6;  // A0 - flexion, A1 - extension, A2 - rotation, Analog input pin that the potentiometer is attached to
const int analogInPin2 = A7;

// const int analogOutPin_f = 10;// Analog output pin that the LED is attached to
// const int analogOutPin_e = 11;
// const int analogOutPin_r = 12;

int sensorValue = 0;        // value read from the pot
int sensorValue2 = 0;    
int data;
//pressurethreshold = 250;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  //pinMode(11, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  // pinMode(analogOutPin_f, OUTPUT);
}

void loop() {
  // read the analog in value:
  //digitalWrite(11,HIGH);
  //digitalWrite(12,HIGH);
  sensorValue = analogRead(analogInPin1);
  sensorValue2 = analogRead(analogInPin2);
  
  // map it to the range of the analog out:
  // outputValue = map(sensorValue, 0, 1023, 0, 500);
  // change the analog out value:
  // digitalWrite(analogOutPin_f, LOW);
  // digitalWrite(analogOutPin_r, HIGH);
  // digitalWrite(analogOutPin_e, LOW);
  // print the results to the serial monitor:
  
  Serial.print("\n sensor X = ");
  Serial.print(sensorValue);

  if (sensorValue<1000){
    if (sensorValue2>250){
    digitalWrite(5, HIGH);
    delay(500);
    digitalWrite(5,LOW);
    digitalWrite(7,LOW);
    }
    else {
    digitalWrite(5, LOW);
    digitalWrite(7,HIGH);
    delay(500);
    digitalWrite(7,LOW);
    
    }
  }  
    else {
      digitalWrite(5,LOW);
      }
  }

