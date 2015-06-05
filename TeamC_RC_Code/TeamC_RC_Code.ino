/*
 Team C Bolt-On Skateboard Propulsion System
 By: Tom Resh, Clinton Best, Matthew Moffa
 Devry University
 Date: 6-2-2015
 Revised: 6-3-2015 CB
 
 Remote controlled skateboard:
 
 Connected RC controller across Channel 2 on tramsmitter
 Then connect to pin 5 in Arduino Uno R3
 Pressure sensor should be connected to pin 0 for input
 
 
 */

int CH2;      // Channel input from RF receiver
int throttle; // Drives Motor Speed
int pwm = 9 ;  //PWM control for motor outputs is connected to pin 9
int sensorPin = 0; // Pressure sensor is connected to pin 0
int sens; // The reading from the FSR square
// Setup for loop, this will run once.
void setup() {
  
  pinMode(5, INPUT); // Set input pin for throttle
  pinMode(pwm, OUTPUT);  //Set control pins to be outputs for PWM
  analogWrite(pwm, 0);
  pinMode(sensorPin, INPUT); // Set input pin for pressure sensor
  
  // For debugging : will send to Serial monitor
  // uncomment to use
  /*
  Serial.begin(9600);
  */
}

// Main code runs here, and runs repeatedtly
void loop() {
  
  sens = analogRead(sensorPin); //get reading from sensor
  
  // For debugging: uncomment to use
  /*
    Serial.print("Analog reading = ");
    Serial.print(sens); // raw analog reading
  */
  
  // check if the weight on the sensor is within the acceptable range
  // This should cover if there isn't enough pressure (user falls off a small child)
  // This should also cover if the user is too big (outside what the motor can handle)
  if (sens > 655 || sens < 900){ 
    CH2 = pulseIn(5, HIGH, 25000); // Channel for Throttle Trigger
    
    throttle = map(CH2, 1000,2000, -500, 500); //center over zero
    throttle = constrain(throttle, -255, 255);
    throttle=abs(throttle); //Pass Only Absolute PWM Values
  
    analogWrite(pwm, throttle);
    
  }
  
  else{
    
    delay(1000); //waits 1 second delay(ms)
  }


}
