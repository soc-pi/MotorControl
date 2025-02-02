# Add source files
add_executable(${PROJECT_NAME} main.c)

# Link the project library
target_link_libraries(${PROJECT_NAME} MotorControl_lib)
