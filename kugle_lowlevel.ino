#include "motor.h"
#include "velocity_controller.h"

// Motor 0 Connections
const int pin_pwm_m0 = 3;
const int pin_enable_a_m0 = A0;
const int pin_enable_b_m0 = A1;
const int pin_encoder_a_m0 = 2;
const int pin_encoder_b_m0 = 7;

// Motor 1 Connections
const int pin_pwm_m1 = 5;
const int pin_enable_a_m1 = A2;
const int pin_enable_b_m1 = A3;
const int pin_encoder_a_m1 = 8;
const int pin_encoder_b_m1 = 10;

// Motor 2 Connections
const int pin_pwm_m2 = 6;
const int pin_enable_a_m2 = A4;
const int pin_enable_b_m2 = A5;
const int pin_encoder_a_m2 = 11;
const int pin_encoder_b_m2 = 12;

// Create an array of motor controllers with the
// above pin assignments.
Motor motors[3] = {
    {pin_pwm_m0, pin_enable_a_m0, pin_enable_b_m0, pin_encoder_a_m0, pin_encoder_b_m0},
    {pin_pwm_m1, pin_enable_a_m1, pin_enable_b_m1, pin_encoder_a_m1, pin_encoder_b_m1},
    {pin_pwm_m2, pin_enable_a_m2, pin_enable_b_m2, pin_encoder_a_m2, pin_encoder_b_m2}
};

// Interrupt service routines for the encoders.
// The Arduino IDE does not let us set class members
// as ISRs, so we wrap them here.
void enc_isr0() {motors[0].onEncoderChange();}
void enc_isr1() {motors[1].onEncoderChange();}
void enc_isr2() {motors[2].onEncoderChange();}

// Create an array of velocity controllers for
// the motors.
VelocityController vel_controllers[3] = {
    {motors[0]}, {motors[1]}, {motors[2]}
};

void setup()
{
    // Setup interrupts on encoders
    attachInterrupt(pin_encoder_a_m0, enc_isr0, CHANGE);
    attachInterrupt(pin_encoder_b_m0, enc_isr0, CHANGE);
    attachInterrupt(pin_encoder_a_m1, enc_isr1, CHANGE);
    attachInterrupt(pin_encoder_b_m1, enc_isr1, CHANGE);
    attachInterrupt(pin_encoder_a_m2, enc_isr2, CHANGE);
    attachInterrupt(pin_encoder_b_m2, enc_isr2, CHANGE);

    // Setup the serial connection
    Serial.begin(9600);
}

void loop() {
    Serial.println(motors[0].getPosition());
    delay(1000);
}