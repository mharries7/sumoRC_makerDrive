/*
 * CODE FOR ROBOT THAT USES ARDUINO UNO, HC-05 AND CYTRON MAKERDRIVE * 
 */

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

// Left motor pins
int leftMotorPWMPin = 6;
int leftMotorDirPin = 9;

// Right motor pins
int rightMotorPWMPin = 10;
int rightMotorDirPin = 11;

void setup() {
  // Initialize motor pins as outputs
  pinMode(leftMotorPWMPin, OUTPUT);
  pinMode(leftMotorDirPin, OUTPUT);
  
  pinMode(rightMotorPWMPin, OUTPUT);
  pinMode(rightMotorDirPin, OUTPUT);

  // Stop motors initially
  rotateMotor(0, 0);

  // Start Dabble communication
  Dabble.begin(9600, 2, 3);
  
  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  int leftMotorSpeed = 0;
  int rightMotorSpeed = 0;

  // Process gamepad input
  Dabble.processInput();

  // Set motor speeds based on gamepad input and print corresponding serial output
  if (GamePad.isUpPressed()) {
    leftMotorSpeed = 255;
    rightMotorSpeed = 255;
  } else if (GamePad.isDownPressed()) {
    leftMotorSpeed = -255; // Negative value for backward movement
    rightMotorSpeed = -255; // Negative value for backward movement
  } else if (GamePad.isLeftPressed()) {
    leftMotorSpeed = -255;
    rightMotorSpeed = 255;
  } else if (GamePad.isRightPressed()) {
    leftMotorSpeed = 255;
    rightMotorSpeed = -255;
  }

  // Rotate motors with the calculated speeds
  rotateMotor(leftMotorSpeed, rightMotorSpeed);
}

void rotateMotor(int leftMotorSpeed, int rightMotorSpeed) {
  // Set direction and speed for the left motor
  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorDirPin, HIGH);    // Reverse direction
    analogWrite(leftMotorPWMPin, leftMotorSpeed);    // Use -leftMotorSpeed to ensure positive value for PWM
  } else {
    digitalWrite(leftMotorDirPin, LOW);     // Forward direction
    analogWrite(leftMotorPWMPin, leftMotorSpeed);
  }

  // Set direction and speed for the right motor
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorDirPin, HIGH);   // Reverse direction
    analogWrite(rightMotorPWMPin, rightMotorSpeed);   // Use -rightMotorSpeed to ensure positive value for PWM
  } else {
    digitalWrite(rightMotorDirPin, LOW);    // Forward direction
    analogWrite(rightMotorPWMPin, rightMotorSpeed); 
  }
}
