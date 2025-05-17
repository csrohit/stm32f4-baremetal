
# STM32F4 Baremetal: Output compare mode in STM32F4 timers

[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)

<!--toc:start-->
- [STM32F4 Baremetal: Output compare mode in STM32F4 timers](#stm32f4-baremetal-output-compare-mode-in-stm32f4-timers)
  - [Description](#description)
  - [Tools Setup](#tools-setup)
  - [Project Structure](#project-structure)
  - [Building](#building)
    - [Compilation](#compilation)
    - [Flashing](#flashing)
  - [Output](#output)
<!--toc:end-->

This guide is meant for embedded developers who wish to get the know how of flow of embedded systems developement. This guide dives in detail about programming embedded sysetems using only the bare-minimum tools mentioned below

1. arm-none-eabi-gcc - Cross Compiler for Arm Cortex M systems
2. Datasheet for target micro-controller
3. Text editor
4. ST Link - Programmer to flash the binary on the board

## Description
Please refer to the medium article for in depth explaination of the code <https://medium.com/@csrohit/output-compare-mode-on-stm32f4-timers-6d961162bbe2>

## Tools Setup

1. GNU toolchain\
   `gcc-arm-none-eabi` ARM cross-platform toolchain is required to build applications for ARM MCUs.
   Toolchain can be installed using package manager by running following command:

   ```bash
   # for Debian-based Linux distros
   sudo apt install gcc-arm-none-eabi

   # for macOS using brew formulae
   brew install arm-none-eabi-gcc
   ```

   Download the latest version of the toolchain from Arm: <https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads>

2. Make tools \
   Make utility is required for configuring and building this project. You can install make on linux by running command:

   ```bash
   # for Debian-based Linux distros
   sudo apt install build-essential

   # for macOS 
   xcode-select --install

   # for macOS using brew formulae
   brew install make
   ```

3. ST Link drivers\
   STM32 Cube Programmer A GUI cum Command Line utility to program any STM32 micro-controller.
   This tool can be downloaded from <https://www.st.com/en/development-tools/stm32cubeprog.html>\
   
   Note: Make sure to add path to `STM32_Programmer_CLI` to `$PATH` environment variable.


## Project Structure

1. `src`\
   This directory contains the source files for the project.
2. `inc`\
   This directory contains the header files required for the project.
3. `stm32f4.ld`\
   This is the linker script required by the linker to create the binary in the layout required by the micro-controller.
4. `Makefile`
   The make script for automating the build process and avoid typing the long compilation commands everytime. For more information on makefile visit [Makefile Tutorial](https://makefiletutorial.com)


## Building

This step involves compiling the source file separately and linking the relocatable object files to generate the final executable object file. In the next step the executable object file is converted into the binary format understood by the micro-controller.
All these steps are automated in the makefile

### Compilation

Run the following command to compile the project and generate executable.

```bash
make all
```

### Flashing

In the final step we flash the generated binary image to the micro-controller.

```bash
make flash
```

following output is observed on the terminal while flashing.

```txt
STM32_Programmer_CLI -c port=SWD ap=0 -w build/i2c_scanner.elf -rst
```

This command flashes the binary image at address `0x8000000` as the _FLASH_ memory starts from that address.

## Output

The LEDs connected to PA6, PA7, PB0, and PB1 will toggle at different intervals, corresponding to the output compare values set for each channel. If you have an oscilloscope or logic analyzer, you can observe these pins switching states precisely as the timer counter matches their compare registers.

The LED connected to PC13 will blink every second, driven by the timer’s update interrupt and the delay function implemented in software.

This setup demonstrates how multiple timer channels can independently control different GPIO pins simultaneously, showcasing the power of STM32 timers for multitasking and precise timing.
