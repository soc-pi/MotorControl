
// main.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "MotorControl.h"

volatile uint8_t running = 1;

void signalHandler(int signum) {
    running = 0;
}

int main(void) {
    // Setup signal handling for clean exit
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    // Initialize motor control
    motorInit();
    printf("Motor control initialized\n");

    // Ramp up test sequence
    printf("Starting motor ramp-up test...\n");
    motorStart();
    
    uint16_t speed = 0;
    const uint16_t speedStep = 100;  // RPM increment
    
    while (running && speed < MOTOR_MAX_RPM) {
        motorSetSpeed(speed);
        printf("Setting speed to %d RPM\n", speed);
        speed += speedStep;
        usleep(500000);  // 500ms delay between speed changes
    }

    // Run at max speed for 5 seconds
    if (running) {
        printf("Running at max speed for 5 seconds...\n");
        motorSetSpeed(MOTOR_MAX_RPM);
        sleep(5);
    }

    // Ramp down
    printf("Ramping down...\n");
    while (running && speed > 0) {
        speed -= speedStep;
        motorSetSpeed(speed);
        printf("Setting speed to %d RPM\n", speed);
        usleep(500000);
    }

    // Stop motor and cleanup
    motorStop();
    printf("Motor stopped\n");

    return 0;
}