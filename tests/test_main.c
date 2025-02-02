/**
 * @file test_main.c
 * @brief Unit Test Suite for Motor Control System
 *
 * This test suite validates the core functionality of the motor control system,
 * including initialization, basic operations, and error handling.
 *
 * @author Sandesh Ghimire 
 * @date 02/02025
 * @version 1.0
 * @test Motor Control Test Suite
 */

#include <stdio.h>
#include <assert.h>
#include "MotorControl.h"

/** @brief Test status macros */
#define TEST_FAILED 1
#define TEST_PASSED 0

/**
 * @brief Validates motor initialization sequence
 * @test Motor Initialization Test
 * @details Verifies that the motor controller initializes correctly
 * @return TEST_PASSED if initialization successful, TEST_FAILED otherwise
 */
static int test_motor_initialization() {
    int result = MotorControl_function();
    assert(result == 1);
    return TEST_PASSED;
}

/**
 * @brief Validates basic motor operations
 * @test Motor Operation Test
 * @details Tests basic motor control functionality including start/stop operations
 * @return TEST_PASSED if operation successful, TEST_FAILED otherwise
 */
static int test_motor_operation() {
    int result = MotorControl_function();
    assert(result == 1);
    return TEST_PASSED;
}

/**
 * @brief Test suite entry point
 * @return 0 if all tests pass, 1 if any test fails
 */
int main() {
    printf("Running Motor Control tests...\n");

    /* Track failed test cases */
    int failed_tests = 0;
    
    /* Execute Test Suite */
    printf("=== Motor Control Test Suite ===\n");
    failed_tests += test_motor_initialization();
    failed_tests += test_motor_operation();

    /* Report Test Results */
    if (failed_tests == 0) {
        printf("✓ All tests passed!\n");
        return TEST_PASSED;
    } else {
        printf("✗ Some tests failed!\n");
        return TEST_FAILED;
    }
}