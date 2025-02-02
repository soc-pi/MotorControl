# Motor Control for Raspberry Pi

## Overview
A comprehensive motor control system for Raspberry Pi utilizing the WiringPi library. Achieve precise speed and direction control of DC motors through PWM signals.

## Prerequisites
- Raspberry Pi (2/3/4)
- Linux-based development PC
- Cross-compilation toolchain
- WiringPi library
- CMake (>= 3.10)

## Hardware Requirements
- 12V DC Motors
- L298N Motor Driver
- 12V Power Supply
- Jumper Wires

## Installation

### Development Machine Setup
```sh
# Install dependencies
./scripts/install_cross_compile.sh

# Clone the repository
git clone https://github.com/yourusername/MotorControl.git
cd MotorControl

# Build the project
mkdir build
cd build
cmake ..
make

# Transfer the executable to Raspberry Pi
scp MotorControl pi@raspberrypi.local:/home/pi/
```

### Raspberry Pi Setup
```sh
# Install WiringPi
sudo apt-get install wiringpi

# Run the motor control program
./MotorControl
```

## Usage
Connect the DC motors to the L298N motor driver and power it with the 12V power supply. Use jumper wires to connect the motor driver to the Raspberry Pi GPIO pins according to the WiringPi pin configuration.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments
- Gordon Henderson for the WiringPi library
- CMake build system
- Raspberry Pi Foundation
- The open-source community