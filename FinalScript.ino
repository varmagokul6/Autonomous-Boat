// Headers
#include "arduinoFFT.h"
#include <Servo.h>


Servo soundServo;
Servo rudderServo;
int soundSensor = A1;

// Variable Definitions
// 1. SOUND SENSOR
#define SAMPLES 128       //Must be a power of 2
#define SAMPLING_FREQUENCY 3700 //Hz, must be less than 10000 due to ADC
#define RANGE 100
int REQ_FREQUENCY = 1760;
/*int MAX_FREQ = 1830;
int MIN_FREQ = 1730;*/
int MAX_FREQ = 1530;
int MIN_FREQ = 1030;

arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];


int turnTime = 3000;  // 3 Seconds to turn


// 4. SERVO MOTOR
// a. Rudder
int rudderPos = 90;
int rudPosinc;          // Increment of Rudder Positioning

// b. Sound Sensor
int soundPos = 90;
int soundPosinc = 30;   // Increment of Sound Sensor Positioning Servo
int detectedPos;
int n = 1;              // Scenario Case (1. Patrol Code; 2. Searching)

// State Definitions

bool S0 = 1;
bool S1 = 0;
bool S2 = 0;
bool S3 = 0;
bool S4 = 0;

void setup() {

  soundServo.attach(11);
  rudderServo.attach(10);
  Serial.begin(115200);
  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));

}

int freq_detect(int pin){
  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
  for(int i=0; i<SAMPLES; i++)
      {
          microseconds = micros();    
       
          vReal[i] = analogRead(pin);
          vImag[i] = 0;
       
          while(micros() < (microseconds + sampling_period_us)){
          }
      }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  //Serial.println(peak);
  delay(1000);
  return (peak);
}

int soundServoMechanism(int servoPos){
  if (servoPos == 0){
    for (soundPos = 0; soundPos <= 180; soundPos += soundPosinc) {
      Serial.print("Sound Pos: ");
      Serial.println(soundPos);
      soundServo.write(soundPos);
      delay(300);             
      float sound = freq_detect(soundSensor);\
      Serial.print("Frequency: ");
      Serial.println(sound);
      if (((sound >= MIN_FREQ) and (sound <= MAX_FREQ))){
        detectedPos = soundPos;
        Serial.print("Detected Pos: ");
        Serial.println(detectedPos);
        n = 2;
        break; 
      }
      
  }
  }
  else if (servoPos == 180){
     for (soundPos = 180; soundPos >= 0; soundPos -= soundPosinc) { 
      Serial.print("Sound Pos: ");
      Serial.println(soundPos);
      soundServo.write(soundPos);            
      delay(300);
      float sound = freq_detect(soundSensor);\
      Serial.print("Frequency: ");
      Serial.println(sound);
      
     if (((sound >= MIN_FREQ) and (sound <= MAX_FREQ))){
        n = 2;
        detectedPos = soundPos;
        break; 
    
  }
  }
  Serial.print("Detected Pos: ");
  Serial.println(detectedPos);
  int count  = 0;     
  double sum = 0;     // sum of Sensor Readings
  double avg = 0;
  float time;
}
}

int patrolCode(){
  rudderServo.write(45);
  delay(1000);
  rudderServo.write(90);
  delay(2000);
  rudderServo.write(135);
  delay(1000);
  
}

void loop() {
  if (n == 1){
    patrolCode();
  }
  soundServoMechanism(soundPos);
  if (n == 2){
    
  }
  //Serial.print("Angle: "); 
  Serial.println(detectedPos);
  if ((detectedPos > 20) and (detectedPos <= 160)){
    rudderServo.write(180 - detectedPos);
    delay(2000);
    /*int startTime = millis();
    while ((millis() - startTime) <= turnTime){
      
      Serial.print("Rudder Pos: ");
      Serial.println(detectedPos);
    }*/
  rudderServo.write(90);
  }
  soundPos = 0;
  delay(2000);

  }
                    
            
