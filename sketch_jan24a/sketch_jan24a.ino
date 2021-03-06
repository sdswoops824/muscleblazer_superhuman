//By the Super Human Team
//Bluetooth

#include <Arduino.h>
#include <IRremote.h>
#include <SimpleTimer.h>

//Functions
void Laser_Sensor();
void repeatEMG();
void IR_Receptor();

//Laser receptor
const int LSpin = A0;// Pin to read the laser sensor
int points = 0;
int LaserValue = 0;

//EMG Sensor
const int emgPin = A1;// Pin to read the EMG sensor
int emg = 0;
int emgcharging = 7;//led to indicate charging
int emgfullcharge = 8;//led to indicate full charge
int emg_counter = 0;

//declare timer
SimpleTimer timer;

// IR receptor
int IR_receptorPin = A2;//Pin used to read IR values
IRrecv irrecv(IR_receptorPin);//Create an object
decode_results results;
int IR_Impact = 5;
int IR_counter = 0;

//Death variable
int end = 0;

void setup() {
        // initialize serial communication at 38400 bits per second:
        Serial.begin(38400);
        pinMode(IR_Impact, OUTPUT);//Turn on pin 5 if we received an impact of IR
        pinMode(emgPin, INPUT);//Turn on pin A1 if we received an impact of IR
        pinMode(emgcharging, OUTPUT);//Turn on when emg charging takes place
        pinMode(emgfullcharge, OUTPUT);//Turn on when IR gun is fully charged
        irrecv.enableIRIn(); // Start the receiver
        timer.setInterval(1000, repeatEMG);//repeats every 1 second/ can be changed
}

void loop() {
        //Read laser sensors
        LaserValue = analogRead(LSpin);
        Laser_Sensor();
        //EMG sensor reading
        timer.run();
        //IR reding
        IR_Receptor();
        //Serial.flush();
        //Serial.write('0');//Avoid errors
}

//Decode
// Read the laser sensor to count the points
void Laser_Sensor() {
        if(LaserValue > 180) {
                if(end < 20) {
                        end=+1;
                        Serial.write('1'); // Sends '1' to the master to count as one point
                }//If we detect that the end variable is over 20 we will do a infinite bucle
                else {
                        while(1) {
                        }
                }
        }
        LaserValue = 0;
}
//Charge the special gun
void repeatEMG() {
        emg = analogRead(emgPin);
        if(emg > 900) {
                digitalWrite(emgcharging,HIGH);
                delay(100);
                digitalWrite(emgcharging,LOW);
                emg_counter = emg_counter + 1;
        }
        else if (emg_counter>10) {
                digitalWrite(emgfullcharge,HIGH);
                delay(200);
                digitalWrite(emgfullcharge,LOW);
                emg_counter = 0;
                Serial.write('2');  // Sends '2' to the master to activate the special gun
        }
}
//Decode the IR pulse
void IR_Receptor() {
        digitalWrite(IR_Impact,LOW);
        if (irrecv.decode(&results)) {
                if (results.decode_type == SONY) {
                        Serial.write('3'); // Sends '3' to the master to advice that we were shoot by IR
                        digitalWrite(IR_Impact,HIGH);//LED will turn on because we were hit
                        delay(500);
                        digitalWrite(IR_Impact,LOW);
                }
        }
}
