#include <stdio.h>
#include <assert.h>
#include "MotorControl.h"

#define TEST_FAILED 1
#define TEST_PASSED 0

static int test_motor_initialization() {
    int result = MotorControl_function();
    assert(result == 1);
    return TEST_PASSED;
}

static int test_motor_operation() {
    int result = MotorControl_function();
    assert(result == 1);
    return TEST_PASSED;
}

int main() {
    printf("Running Motor Control tests...\n");

    int failed_tests = 0;
    
    // Test Suite
    failed_tests += test_motor_initialization();
    failed_tests += test_motor_operation();

    if (failed_tests == 0) {
        printf("All tests passed!\n");
        return TEST_PASSED;
    } else {
        printf("Some tests failed!\n");
        return TEST_FAILED;
    }
}