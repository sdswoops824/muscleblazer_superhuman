
//Libraries
#include <IRremote.h>
#include <SimpleTimer.h>

//code values
const int Laser_PullUPin = 2;  //pin for pullup resistor D2
int ledLaser =  13;         //pin for laser
int emgcharging = 7;
int emgfullcharge = 8;
int IRstate = 0;
int value = 0;
int lastvalue = 0;     // previous state of the button

//decode
//counter to begin the game
int count = 0;

//Receptor
int points = 0;
const int analogInPin = A0;
int LaserValue = 0;
int PointC = A1;//By this pin we will send the data to the OLED display for points

//EMG Sensor
int emg = 0;
int emgPin = A2;
int emg_counter = 0;

//timer object
SimpleTimer timer;

//IR
IRsend irsend;
const int analogPin = A3;
int outputvalue = 0;

// IR receptor
int IR_receptorPin = 12;//Before was 11
IRrecv irrecv(IR_receptorPin);
decode_results results;
const int IR_PullUPin = 3;  //pin for pullup resistor D3
int IR_Value = 0;
int IR_Last_Value = 0;

//Death variable
int end = 0;

// EMG function to be executed periodically, each second/ minute (adjust accordingly)
void repeatMe() {
    emg = analogRead(emgPin);
    if(emg>900){
      
      digitalWrite(7,HIGH);
      delay(500);
      digitalWrite(7,LOW);

      emg_counter = emg_counter + 1;
      }

      else if (emg_counter>20) {
        digitalWrite(8,HIGH);
        delay(500);
        digitalWrite(8,LOW);
        emg_counter = 0; 
        IRstate = 1;      
        }

    Serial.print("Uptime (s): ");
    Serial.println(millis() / 1000);
    Serial.print("\n count =");
    Serial.print(emg_counter);
}

void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(emgcharging, OUTPUT);
  pinMode(emgfullcharge, OUTPUT);
  pinMode(ledLaser, OUTPUT);  //Set pin 13 as output
  pinMode(PointC, OUTPUT);  //Set pin 11 as output
  Serial.begin(9600);      //Start serial communication
  timer.setInterval(1000, repeatMe);
}

void loop() {
  value = digitalRead(Laser_PullUPin);  //read the digital input
  Laser_PullUp();
  LaserValue = analogRead(analogInPin);
  delay(10);
  //  Serial.print(LaserValue);
  //  Serial.print("\n");
  Points();
  
  //EMG sensor reading
  timer.run();//run timer for EMG
  
  //IR reding
  IR_Value = digitalRead(IR_PullUPin);
}

//Encode
void Laser_PullUp() {
  if (value != lastvalue) {
    if (value == HIGH) {
        SendPluse(); //I call the function pulse
        delay(10);
    }
  }
  lastvalue = value;//Evaluate the last state of the push buttom
}

void SendPluse() {
  //We will send 1 pulse
  digitalWrite(ledLaser, HIGH);
  delay(1000);
  digitalWrite(ledLaser, LOW);
  delay(2);
}

//decode
void Points() {
  if(LaserValue > 180) {
    if(end < 20) {
      end=+1;
      digitalWrite(PointC, HIGH);
      delay(1000);
      digitalWrite(PointC, LOW);
    }//If we detect that the end variable is over 20 we will do a infinite bucle
    else {
      while(1) {
        digitalWrite(PointC, HIGH);
      }
    }
  }
  LaserValue = 0;
}

void EMG() {
  if(emg > 900) {
    emg_counter=+1;
    if(emg_counter = 100000) { //If the count is over 20 we will activate the super arm
      emg_count=+1;
      digitalWrite(5,HIGH);//temp
      Serial.print("\nfirst count =");
      Serial.print(emg_counter);
      delay(500);      
      Serial.print("\nsecond count =");
      Serial.print(emg_count);
      digitalWrite(5,LOW);//temp
      emg_counter = 0;  
      
      if(emg_count = 20) {
        digitalWrite(6,HIGH);//temp
        Serial.print("\nsecond count =");
        Serial.print(emg_count);
        delay(500);
        digitalWrite(6,LOW);//temp
        irsend.sendSony(0x68B90, A3);// the second statment is the port that we will use
        delay(100);
        emg_count = 0;
        }         
     }
     else
       end;
  }
  }

 void countEMG(){
     
  }

void IR_PullUp() {
  if (IR_Value != IR_Last_Value) {
    if (IR_Value == HIGH) {
        IR_Receptor(); //I call the function pulse
        delay(10);
    }
  }
  IR_Last_Value = IR_Value;//Evaluate the last state IR sensor Pin
}

void IR_Receptor() {
  digitalWrite(5,LOW);
  if (irrecv.decode(&results)) {
    if (results.decode_type == SONY) {
      digitalWrite(5,HIGH);
      delay(30);
      //Here we will write the extra IR points
    }
    irrecv.resume(); // Receive the next value
  }
}
