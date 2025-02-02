cmake_minimum_required(VERSION 3.10)
project(MotorControl)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)


add_executable(test_motor_control test_main.c)
target_link_libraries(test_motor_control motor_control)

add_test(NAME test_motor_control COMMAND test_motor_control)