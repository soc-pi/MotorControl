// MotorControl.h
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>

// Motor specifications
#define MOTOR_VOLTAGE 24
#define MOTOR_MAX_RPM 5000
#define NUM_POLES 8  // Typical for BLDC motors, adjust as per your motor

// PWM configuration
#define PWM_FREQUENCY 20000  // 20kHz
#define PWM_RANGE 1024      // PWM resolution

// GPIO pins for the three phases
#define PHASE_A_PIN 18  // PWM0
#define PHASE_B_PIN 19  // PWM1
#define PHASE_C_PIN 20  // PWM2

// Hall sensor pins
#define HALL_A_PIN 23
#define HALL_B_PIN 24
#define HALL_C_PIN 25

// Function declarations
void motorInit(void);
void motorSetSpeed(uint16_t rpm);
void motorStop(void);
void motorStart(void);
uint16_t motorGetSpeed(void);
void updateCommutation(void);

#endif // MOTOR_CONTROL_H
