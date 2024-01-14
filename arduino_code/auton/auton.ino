#define M1_1_PIN 3
#define M1_2_PIN 5

#define M2_1_PIN 6
#define M2_2_PIN 9

#define TRIG_PIN A0
#define ECHO_PIN A1

#include <Arduino.h>
#include "HX711.h"

#define DOUT  1
#define CLK  0

HX711 scale;
float calibration_factor = -7050; //-7050 worked for someone's 440lb max scale setup


void setMotor1PWM(float p) {
  setMotorGenericPWM(p, M1_1_PIN, M1_2_PIN);
}

void setMotor2PWM(float p) {
  setMotorGenericPWM(p, M2_1_PIN, M2_2_PIN);
}

void setMotorGenericPWM(float p, int pin1, int pin2) {
  if (p > 1.0) {
    p = 1.0;
  } else if (p < -1.0) {
    p = -1.0;
  }

  if (p == 0.0) {
    analogWrite(pin1, 0);
    analogWrite(pin2, 0);
  }

  else if (p > 0) {
    analogWrite(pin1, p * 255.0);
    analogWrite(pin2, 0);
  } else {
    analogWrite(pin1, 0);
    analogWrite(pin2, -p * 255.0);
  }
}

float read_distance() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  float duration_us = pulseIn(ECHO_PIN, HIGH);


  // calculate the distance
  return 0.017 * duration_us;
}


void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(M1_1_PIN, OUTPUT);
  pinMode(M1_2_PIN, OUTPUT);
  pinMode(M2_1_PIN, OUTPUT);
  pinMode(M2_2_PIN, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

}

void loop() {
  // put your main code here, to run repeatedly:

//  float distance_cm = read_distance();

//  setMotor1PWM(0.75);
//  setMotor2PWM(0.75);
//
//  while(read_distance() > 7) {
//    delay(20);
//  }
//  setMotor1PWM(0);
//  setMotor2PWM(0);
//  delay(400);
//  setMotor1PWM(0);
//  setMotor2PWM(-0.75);
//  delay(1000);
//
//  setMotor1PWM(0);
//  setMotor2PWM(0);
//  delay(400);


  scale.set_scale(calibration_factor);

  float units = scale.get_units();

  if (units > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
 

}
