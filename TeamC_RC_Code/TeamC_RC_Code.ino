/*

  Team C Bolt-On Skateboard Propulsion System

  By: Tom Resh, Clinton Best, Matthew Moffa

  Devry University

  Date: 6-2-2015

  Revised: 6-20-2015 CB


  Remote controlled skateboard:

  Connected RC controller across Channel 2 on tramsmitter

  Then connect to pin 5 in Arduino Uno R3

  FSR Pressure sensor (fsr) should be connected to pin 0 for input

  Distance sensor (dss) should be connected to pin 7 for input

  */

int rfc;      // Channel input from RF receiver
int throttle; // Variable for throttle measurement
const int pwm = 9 ;  //Pin for motor outputs
const int  pss = 0; //Pin for FSR pressure sensor
float fsr = 0; // The reading from the FSR square
const int dss = 7 ; //Pin for distance sensor
long duration, cm; //Variables for distance measurements

// Setup for loop, this will run once.

void setup() {

  pinMode(5, INPUT); // Set input pin for throttle
  pinMode(pwm, OUTPUT);  //Set control pins to be outputs for PWM
  analogRead(0);
  analogWrite(pwm, 0);
  Serial.begin(9600); // initializes serial communication


}

// Main code runs here, and runs repeatedtly

void loop() {

  fsr = analogRead(pss); //reads  load fsr input

  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(dss, OUTPUT);
  digitalWrite(dss, LOW);
  delayMicroseconds(2);
  digitalWrite(dss, HIGH);
  delayMicroseconds(5);
  digitalWrite(dss, LOW);

  // Using same pin to read returned signal from dss
  pinMode(dss, INPUT);
  duration = pulseIn(dss, HIGH);

  // Convert the time into cm
  cm = microsecondsToCentimeters(duration);

  // Check if the weight on the fsr is within the acceptable range
  // This should cover if there isn't enough pressure (user falls off a small child)
  // This should also cover if the user is too big (outside what the motor can handle)
  // Also check if distance fsr sees something within 5 feet.

  if (fsr > 700 && fsr < 900 && cm < 153 ) {

    rfc = pulseIn(5, HIGH, 25000); // Channel for Throttle Trigger
    throttle = map(rfc, 1000, 2000, -500, 500); //center over zero
    throttle = constrain(throttle, -255, 255);
    throttle = abs(throttle); //Pass Only Absolute PWM Values
    analogWrite(pwm, throttle);
    delay(100);

  }

  // Otherwise ignore signals from controller
  else {

    analogWrite(pwm, 0);
    delay(1000); //waits 1 second delay(ms)

  }

}

// function that converts time to CM
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
