#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin



const int trigPin = 7;
const int echoPin = 10;

long duration;
int distance;
int trig_dist = 100;

void setup() {
  Serial.begin(9600); // Starts the serial communication
  // Attach the ESC on pin 9
  ESC.attach(9); // (pin, min pulse width, max pulse width in microseconds)
  delay(10);
  ESC.write(10);
  delay(5000);
  ESC.write(180);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 
  
}


void loop()
{


  // DISTANCE SENSING CODE: DO NOT TOUCH
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance >= trig_dist){
    ESC.write(180);
  }
  else{
    ESC.write(0);
  }
  delay(1000);
}
