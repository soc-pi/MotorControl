#!/bin/bash

# Script to install packages and cross-compile WiringPi for Raspberry Pi
echo "Installing cross-compilation packages and building WiringPi..."

# Exit on any error
set -e

# Update package repositories
sudo apt-get update

# Install essential packages
sudo apt-get install -y build-essential
sudo apt-get install -y cmake
sudo apt-get install -y git

# Install cross-compilation toolchain
sudo apt-get install -y crossbuild-essential-armhf
sudo apt-get install -y gcc-arm-linux-gnueabihf
sudo apt-get install -y g++-arm-linux-gnueabihf

# Verify installation
if ! command -v arm-linux-gnueabihf-gcc >/dev/null 2>&1; then
    echo "Error: Failed to install cross-compilation toolchain"
    exit 1
fi

# Clone WiringPi repository
if [ ! -d "WiringPi" ]; then
    git clone https://github.com/WiringPi/WiringPi.git
else
    echo "WiringPi repository already exists, pulling latest changes..."
    cd WiringPi
    git pull
    cd ..
fi
cd WiringPi

# Set cross-compilation environment variables
export CC=arm-linux-gnueabihf-gcc
export CXX=arm-linux-gnueabihf-g++
export AR=arm-linux-gnueabihf-ar
export LD=arm-linux-gnueabihf-ld
export CFLAGS="-march=armv6 -mfpu=vfp -mfloat-abi=hard"

# Build WiringPi
./build debian

echo "WiringPi cross-compilation completed successfully"
echo "The compiled libraries can be found in: $(pwd)"
