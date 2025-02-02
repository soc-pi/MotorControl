# Create a library called "MotorControl"
add_library(MotorControl_lib MotorControl.c)

# Specify include directories for the library
target_include_directories(MotorControl_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
