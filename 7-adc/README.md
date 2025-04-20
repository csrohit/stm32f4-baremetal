# STM32F4 Baremetal: Logging information over USART

<!--toc:start-->

- [STM32F4 Baremetal: Create a Makefile Project](#stm32f4-baremetal-create-a-makefile-project)
  - [Tools Setup](#tools-setup)
  - [Project Structure](#project-structure)
  - [Makefile](#makefile)
  - [Building](#building)
    - [Compilation](#compilation)
    - [Flashing](#flashing)
  - [Output](#output)
  <!--toc:end-->

[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)

This guide is meant for embedded developers who wish to get the know how of flow of embedded systems developement. This guide dives in detail about programming embedded sysetems using only the bare-minimum tools mentioned below

1. arm-none-eabi-gcc - Cross Compiler for Arm Cortex M systems
2. Datasheet for target micro-controller
3. Text editor
4. ST Link - Programmer to flash the binary on the board

In this second step. we strip the startup code from the `main.c` file and create a separate startup script.

## Tools Setup

1. GNU toolchain

   - for debian based systems:

   ```bash
   sudo apt install build-essential
   ```

   - for Mac OS

   ```bash
   brew install gcc-arm-embedded
   ```

2. ST Link drivers

   - for debian based systems

   ```bash
   sudo apt install stlink-tools
   ```

   - for Mac OS

   ```bash
   brew install stlink
   ```

## Project Structure

1. `src/main.c`\
   The main function for the application, separated from the startup code. initializes the peripherals and infinitely blinks the LED.
2. `src/startup_stm32f4.c`\
   The startup script for the micro-controller, stripped from `src/main.c`.
3. `stm32f4.ld`\
   This is the linker script required by the linker to create the binary in the layout required by the micro-controller.
4. `Makefile`\
   The make script for automating the build process and avoid typing the long compilation commands everytime. For more information on makefile visit [Makefile Tutorial](https://makefiletutorial.com)

## Makefile

We use `make` utility to automate the task of building and linking the source code. The `make` utility requires `Makefile` which defines the set of tasks to be executed.

1. Set variables for executable name, linker script and toolchain\

   ```make
   TARGET = blink

   LDSCRIPT  = stm32f4.ld

   PREFIX      =   arm-none-eabi
   CC          =   ${PREFIX}-gcc
   LD       =   ${PREFIX}-ld
   AS       =   ${PREFIX}-as
   GDB      =   ${PREFIX}-gdb
   OBJCOPY     =   ${PREFIX}-objcopy
   SIZE      =   ${PREFIX}-size
   ```

2. Set flags for compilation and linking\

   ```Makefile
   MCU_FLAGS  = -mcpu=cortex-m4 -mfloat-abi=soft -mthumb

   LDFLAGS     := $(MCU_FLAGS) -nostdlib
   CFLAGS      := $(MCU_FLAGS) -nostdlib -Os
   ```

3. Generated list of source files and respective object files\
   The following snippet finds all the `.c` files in `src` directory and adds it to sources list. In the next line the sources are converted into respective object list.

   ```Makefile
   SRC_DIRS    := src
   BUILD_DIR   := build

   SRCS        := $(shell find $(SRC_DIRS) -name '*.c')
   OBJS        := $(SRCS:%.c=$(BUILD_DIR)/%.o)
   ```

4. Define targets\
    The following snippet defines targets for generating the binary file.
   - `all` - default target depends upon `size` and `bin`.
   - `elf` - target for executable object file
   - `bin` - target for flashable binary image file
   - `size` - displays the section wise memory usage
   - `flash` - target to upload the binary to the micro-controller
   - `clean` - target to clean all the build files
     🗃️

## Building

This step involves compiling the source file separately and linking the relocatable object files to generate the final executable object file. In the next step the executable object file is converted into the binary format understood by the micro-controller.
All these steps are automated in the makefile

### Compilation

Run the following command to compile the `main.c` file and generate executable.

```bash
make all
```

### Flashing

In the final step we flash the generated binary image to the micro-controller.

```bash
make flash
```

This command flashes the binary image at address `0x8000000` as the _FLASH_ memory starts from that address.

## Output

After flashing successfully the LED should be Blinking.
