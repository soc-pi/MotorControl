
// MotorControl.c
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "MotorControl.h"

// Commutation sequence for each hall sensor state (0-7)
static const uint8_t commutationTable[8][3] = {
    {0, 0, 0}, // 0 - Invalid state
    {1, 0, 0}, // 1
    {0, 1, 0}, // 2
    {1, 1, 0}, // 3
    {0, 0, 1}, // 4
    {1, 0, 1}, // 5
    {0, 1, 1}, // 6
    {0, 0, 0}  // 7 - Invalid state
};

static uint16_t currentSpeed = 0;
static uint8_t isRunning = 0;
static uint16_t pwmDutyCycle = 0;

void motorInit(void) {
    // Initialize wiringPi
    if (wiringPiSetup() == -1) {
        printf("WiringPi initialization failed\n");
        return;
    }

    // Setup PWM pins
    pinMode(PHASE_A_PIN, PWM_OUTPUT);
    pinMode(PHASE_B_PIN, PWM_OUTPUT);
    pinMode(PHASE_C_PIN, PWM_OUTPUT);

    // Initialize software PWM
    softPwmCreate(PHASE_A_PIN, 0, PWM_RANGE);
    softPwmCreate(PHASE_B_PIN, 0, PWM_RANGE);
    softPwmCreate(PHASE_C_PIN, 0, PWM_RANGE);

    // Setup hall sensor pins as inputs with pull-up resistors
    pinMode(HALL_A_PIN, INPUT);
    pinMode(HALL_B_PIN, INPUT);
    pinMode(HALL_C_PIN, INPUT);
    pullUpDnControl(HALL_A_PIN, PUD_UP);
    pullUpDnControl(HALL_B_PIN, PUD_UP);
    pullUpDnControl(HALL_C_PIN, PUD_UP);

    // Initial state
    motorStop();
}

void motorSetSpeed(uint16_t rpm) {
    if (rpm > MOTOR_MAX_RPM) {
        rpm = MOTOR_MAX_RPM;
    }
    
    currentSpeed = rpm;
    pwmDutyCycle = (rpm * PWM_RANGE) / MOTOR_MAX_RPM;
    
    if (isRunning) {
        updateCommutation();
    }
}

void motorStop(void) {
    isRunning = 0;
    softPwmWrite(PHASE_A_PIN, 0);
    softPwmWrite(PHASE_B_PIN, 0);
    softPwmWrite(PHASE_C_PIN, 0);
}

void motorStart(void) {
    isRunning = 1;
    updateCommutation();
}

uint16_t motorGetSpeed(void) {
    return currentSpeed;
}

void updateCommutation(void) {
    if (!isRunning) return;

    // Read hall sensors
    uint8_t hallState = 0;
    hallState |= digitalRead(HALL_A_PIN) << 2;
    hallState |= digitalRead(HALL_B_PIN) << 1;
    hallState |= digitalRead(HALL_C_PIN);

    // Apply commutation pattern
    const uint8_t* pattern = commutationTable[hallState];
    
    softPwmWrite(PHASE_A_PIN, pattern[0] ? pwmDutyCycle : 0);
    softPwmWrite(PHASE_B_PIN, pattern[1] ? pwmDutyCycle : 0);
    softPwmWrite(PHASE_C_PIN, pattern[2] ? pwmDutyCycle : 0);
}
