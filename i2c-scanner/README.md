
<!--toc:start-->
- [STM32F4 Baremetal: Scan Connected I2C devices](#stm32f4-baremetal-scan-connected-i2c-devices)
  - [Tools Setup](#tools-setup)
  - [Project Structure](#project-structure)
  - [Building](#building)
    - [Compilation](#compilation)
    - [Flashing](#flashing)
  - [Output](#output)
<!--toc:end-->

# STM32F4 Baremetal: Scan Connected I2C devices
[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)

This guide is meant for embedded developers who wish to get the know how of flow of embedded systems developement. This guide dives in detail about programming embedded sysetems using only the bare-minimum tools mentioned below

1. arm-none-eabi-gcc - Cross Compiler for Arm Cortex M systems
2. Datasheet for target micro-controller
3. Text editor
4. ST Link - Programmer to flash the binary on the board

In this second step. we strip the startup code from the `main.c` file and create a separate startup script.

## Tools Setup

1. GNU toolchain
    `gcc-arm-none-eabi` ARM cross-platform toolchain is required to build applications for ARM MCUs.
    Toolchain can be installed by running following command:

   ```bash
    # for Debian-based Linux distros
    sudo apt install gcc-arm-none-eabi

    # for macOS using brew formulae
    brew install arm-none-eabi-gcc
   ```

2. Make tools 
    Make utility is required for configuring and building this project. You can install make on linux by running command:

2. ST Link drivers
    STM32 Cube Programmer A GUI cum Command Line utility to program any STM32 micro-controller.
    This tool can be downloaded from https://www.st.com/en/development-tools/stm32cubeprog.html

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
      -------------------------------------------------------------------
                        STM32CubeProgrammer v2.15.0                  
      -------------------------------------------------------------------

ST-LINK SN  : 370C0B002A135937334D4E00
ST-LINK FW  : V2J45S7
Board       : --
Voltage     : 3.19V
SWD freq    : 4000 KHz
Connect mode: Normal
Reset mode  : Software reset
Device ID   : 0x423
Revision ID : Rev Z
Device name : STM32F401xB/C
Flash size  : 256 KBytes
Device type : MCU
Device CPU  : Cortex-M4
BL Version  : 0xD1



Memory Programming ...
Opening and parsing file: i2c_scanner.elf
  File          : i2c_scanner.elf
  Size          : 21.32 KB 
  Address       : 0x08000000 


Erasing memory corresponding to segment 0:
Erasing internal memory sectors [0 1]
Download in Progress:
[==================================================] 100% 

File download complete
Time elapsed during download operation: 00:00:00.707

MCU Reset

Software reset is performed
```

This command flashes the binary image at address `0x8000000` as the _FLASH_ memory starts from that address.

## Output

The I2C bus is scanned for available devices every 5 seconds. All the detected devices are listed using USART console.
The LED connected to pin PC13 blinks at every iteration as sign-of-life.
![List of devices detected by scanner](../docs/out.png)
