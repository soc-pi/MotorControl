/**
 * @file MotorControl.h
 * @brief Header file for BLDC Motor Control System
 *
 * This header defines the interface for controlling a 3-phase BLDC motor
 * using Hall effect sensors for commutation and PWM for speed control.
 * It includes function declarations for motor initialization, speed control,
 * and commutation updates.
 *
 * @version 1.1
 * @date 2025-02-01
 * @license MIT
 */

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>

/** @brief Motor voltage in volts */
#define MOTOR_VOLTAGE 24

/** @brief Maximum motor speed in RPM */
#define MOTOR_MAX_RPM 5000

/** @brief Number of poles in the motor */
#define NUM_POLES 8  // Typical for BLDC motors, adjust as per your motor

/** @brief PWM frequency in Hz */
#define PWM_FREQUENCY 20000  // 20kHz

/** @brief PWM resolution */
#define PWM_RANGE 1024  // PWM resolution

/** @brief GPIO pin for Phase A (PWM capable) */
#define PHASE_A_PIN 18  // PWM0

/** @brief GPIO pin for Phase B (PWM capable) */
#define PHASE_B_PIN 19  // PWM1

/** @brief GPIO pin for Phase C (PWM capable) */
#define PHASE_C_PIN 20  // PWM2

/** @brief GPIO pin for Hall sensor A */
#define HALL_A_PIN 23

/** @brief GPIO pin for Hall sensor B */
#define HALL_B_PIN 24

/** @brief GPIO pin for Hall sensor C */
#define HALL_C_PIN 25

/**
 * @brief Initialize motor control hardware
 * @return 0 on success, -1 on failure
 * @note Performs self-test of all subsystems
 * @warning Requires root privileges for GPIO access
 */
int motorInit(void);

/**
 * @brief Set motor speed with safety constraints
 * @param rpm Desired speed (0-MOTOR_MAX_RPM)
 * @note Implements soft ramping for speed changes
 * @warning Speed changes are rate-limited
 */
void motorSetSpeed(uint16_t rpm);

/**
 * @brief Stop the motor
 * @details Immediately stops motor by de-energizing all phases
 */
void motorStop(void);

/**
 * @brief Start the motor
 * @details Enables commutation and applies current speed setting
 */
void motorStart(void);

/**
 * @brief Get current motor speed
 * @return Current speed in RPM
 */
uint16_t motorGetSpeed(void);

/**
 * @brief Update motor phase commutation
 * @details Reads Hall sensors and applies appropriate phase pattern
 * @note Only operates when motor is running (isRunning == 1)
 */
void updateCommutation(void);

#endif // MOTOR_CONTROL_H