/**
 * @file main.c
 * @brief Motor Control System Main Program
 *
 * This program implements a motor control test sequence with ramp-up/down
 * functionality and safety features. It handles graceful shutdown on
 * system interrupts and provides real-time speed control.
 *
 * @author Sandesh Ghimire
 * @date 02/02/2025
 * @version 1.0
 * @Changes :
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "MotorControl.h"

/** @brief Flag to control program execution */
volatile uint8_t running = 1;

/**
 * @brief Signal handler for graceful shutdown
 * @param signum Signal number received
 * @note Handles SIGINT and SIGTERM
 */
void signalHandler(int signum) {
    running = 0;
}

/**
 * @brief Main program entry point
 * @return 0 on successful execution, non-zero on error
 */
int main(void) {
    /* System initialization */
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    /* Motor initialization phase */
    motorInit();
    printf("Motor control initialized\n");

    /* TEST SEQUENCE 1: Ramp-up phase */
    printf("Starting motor ramp-up test...\n");
    motorStart();
    
    uint16_t speed = 0;
    const uint16_t speedStep = 100;  // RPM increment per step
    
    /* Gradual speed increase loop */
    while (running && speed < MOTOR_MAX_RPM) {
        motorSetSpeed(speed);
        printf("Setting speed to %d RPM\n", speed);
        speed += speedStep;
        usleep(500000);  // 500ms control loop interval
    }

    /* TEST SEQUENCE 2: Maximum speed test */
    if (running) {
        printf("Running at max speed for 5 seconds...\n");
        motorSetSpeed(MOTOR_MAX_RPM);
        sleep(5);  // Sustained maximum speed test
    }

    /* TEST SEQUENCE 3: Ramp-down phase */
    printf("Ramping down...\n");
    while (running && speed > 0) {
        speed -= speedStep;
        motorSetSpeed(speed);
        printf("Setting speed to %d RPM\n", speed);
        usleep(500000);  // Controlled deceleration interval
    }

    /* System shutdown sequence */
    motorStop();
    printf("Motor stopped\n");

    return 0;
}