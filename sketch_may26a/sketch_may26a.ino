
// SD Card Module
#include <SPI.h>
#include <SD.h>

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

// Infrared Module
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Adafruit_NECremote.h"

#define IRpin         4
Adafruit_NECremote remote(IRpin);

// Traffic Lights - LED Outputs
#define ledRed A0
#define ledYellow A1 
#define ledGreen A2

// DC Motor & Motor Module - L298N
#include <L298N.h>

// Pin definition
const unsigned int IN1 = 5;
const unsigned int IN2 = 6;
const unsigned int EN = 9;

// Create one motor instance
L298N motor(EN, IN1, IN2);

// Servo
#include <Servo.h>
Servo myservo;

//Potentiometer
#define pot A3

// Piezo Buzzer
#define piezoPin 8

// Sonar - HC-SR04
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin A4 //attach pin D3 Arduino to pin Trig of HC-SR04

// Line Sensor
#define lineSensorPin 3

int lastcode = -1;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:

pinMode(lineSensorPin, OUTPUT);
Serial.begin(9600);           // Open serial communications and wait for port to open:
  while (!Serial) {
    delay(1);                   // wait for serial port to connect. Needed for native USB port only
  }

//// SD Card initialisation
//  Serial.print("Initializing SD card...");
//  if (!SD.begin(10)) {
//    Serial.println("initialization failed!");
//    while (1);
//  }
//// Real Time Clock (RTC)
//  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
//  Serial.println("initialization done.");
//logEvent("System Initialisation...");

// Traffic Lights - LED Outputs
pinMode(ledRed, OUTPUT);
pinMode(ledYellow, OUTPUT);
pinMode(ledGreen, OUTPUT);

// DC Motor & Motor Module - L298N
motor.setSpeed(70);

// Servo
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

//Potentiometer
pinMode(pot, INPUT);

// Piezo Buzzer
pinMode(piezoPin,OUTPUT);

// Sonar - HC-SR04
pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT


}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  

remoteDecode();
SonarSequence();
LineSensorSequence();
PotentiometerValue();
motorDC();
}

String remoteDecode() {
  int c = remote.listen(5);  // seconds to wait before timing out!
  // Or you can wait 'forever' for a valid code
  //int c = remote.listen();  // Without a #, it means wait forever
  if (c >= 0) {
    switch (c) {

        Serial.println("Code is :" + c);
      // Top keys
      case 70:
        return "UP";
        break;
      case 21:
        return"DOWN";
        break;
      case 68:
        Serial.println("LEFT");
        break;
      case 67:
        Serial.println("RIGHT");
        break;
      case 64:
        Serial.println("OK");
        break;
 
}
  }
}

void motorDC(){
motor.forward();
delay(1000);
motor.stop();
delay(1000);
motor.backward();
delay(1000);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RemoteSequence(){
if (remoteDecode() == "UP")
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SonarSequence(){

  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LineSensorSequence(){

  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PotentiometerValue() {

  
}















  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void logEvent(String dataToLog) {
  /*
     Log entries to a file on an SD card.
  */
  // Get the updated/current time
  DateTime rightNow = rtc.now();

  // Open the log file
  File logFile = SD.open("events.csv", FILE_WRITE);
  if (!logFile) {
    Serial.print("Couldn't create log file");
    abort();
  }

  // Log the event with the date, time and data
  logFile.print(rightNow.year(), DEC);
  logFile.print(",");
  logFile.print(rightNow.month(), DEC);
  logFile.print(",");
  logFile.print(rightNow.day(), DEC);
  logFile.print(",");
  logFile.print(rightNow.hour(), DEC);
  logFile.print(",");
  logFile.print(rightNow.minute(), DEC);
  logFile.print(",");
  logFile.print(rightNow.second(), DEC);
  logFile.print(",");
  logFile.print(dataToLog);

  // End the line with a return character.
  logFile.println();
  logFile.close();
  Serial.print("Event Logged: ");
  Serial.print(rightNow.year(), DEC);
  Serial.print(",");
  Serial.print(rightNow.month(), DEC);
  Serial.print(",");
  Serial.print(rightNow.day(), DEC);
  Serial.print(",");
  Serial.print(rightNow.hour(), DEC);
  Serial.print(",");
  Serial.print(rightNow.minute(), DEC);
  Serial.print(",");
  Serial.print(rightNow.second(), DEC);
  Serial.print(",");
  Serial.println(dataToLog);
}
