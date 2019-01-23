// Code for Arduino control of 28-BYJ48 stepper motor

#include <Stepper.h>

// Number of steps per revolution for 28-BYJ48 stepper motor
#define STEPS 32

// create an instance of the stepper class using the steps and pins
Stepper stepper(STEPS, 8, 10, 9, 11);

int val = 0;

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(200);
}

void loop() {
  if (Serial.available()>0)
  {
    val = Serial.parseInt();
    stepper.step(val);
    Serial.println(val); //for debugging
  }
 
}
