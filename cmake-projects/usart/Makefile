TARGET      := i2c-scanner

# debug build?Release
BUILD_TYPE  = Release

TRIPLE      =   arm-none-eabi
CC          =   ${TRIPLE}-gcc
CXX         =   ${TRIPLE}-g++
LD 		    =   ${TRIPLE}-ld
AS 		    =   ${TRIPLE}-as
GDB 	    =   ${TRIPLE}-gdb
OBJCOPY     =   ${TRIPLE}-objcopy



INC_DIRS    := include lib/usart lib/gpio lib/system
SRC_DIRS    := src lib/usart lib/gpio lib/system
BUILD_DIR   := build

SRCS        := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS        := $(SRCS:%.cpp=$(BUILD_DIR)/%.o) 
DEFS        := -DSTM32F401xE

CPP_FLAGS 	:= $(addprefix -I,$(INC_DIRS)) $(DEFS)
CPU_FLAGS   := -mcpu=cortex-m4 -mfloat-abi=soft -mthumb
C_FLAGS     := -std=c++17 -Os -Wall -fdata-sections -ffunction-sections -fno-exceptions -fno-rtti --specs=nano.specs -fno-threadsafe-statics 
LD_FLAGS    := $(CPU_FLAGS) --specs=nano.specs -Wl,--gc-sections

ifeq ($(BUILD_TYPE), Debug)
C_FLAGS 	+= -g -gdwarf-2
endif

# Generate dependency information
C_FLAGS     += -MMD -MP 

# binary file to flash on target
all : bin
bin : $(BUILD_DIR)/$(TARGET).bin

%.bin: %.elf
	@echo "COPY " $< " => " $@
	@$(OBJCOPY) -Obinary $(*).elf $(*).bin

# executable object files for debugging
%.hex: %.elf
	$(OBJCOPY) -Oihex $(*).elf $(*).hex

%.srec: %.elf
	$(OBJCOPY) -Osrec $(*).elf $(*).srec

%.list: %.elf
	$(OBJDUMP) -S $(*).elf > $(*).list

%.size: %.elf
	@echo "Section wise usage: "
	@$(SIZE) $<

$(BUILD_DIR)/$(TARGET).elf: $(OBJS) 
	$(CC) $(LD_FLAGS) -o $@ $(OBJS) -Tstm32f4.ld -Wl,-Map="$(BUILD_DIR)/$(TARGET).map",--gc-sections,-cref,--print-memory-usage

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPU_FLAGS) $(CPP_FLAGS) $(C_FLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPP_FLAGS) $(CPU_FLAGS) $(C_FLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(ASFLAGS) -c $< -o $@

flash: bin
	STM32_Programmer_CLI -c port=SWD ap=0 -w $(BUILD_DIR)/$(TARGET).elf -rst

erase:
	STM32_Programmer_CLI -c port=SWD ap=0 -e all

reset:
	STM32_Programmer_CLI -c port=SWD ap=0  -rst

flashv2:
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000

flash-openocd:
	openocd -d2 -f interface/stlink.cfg -c "transport select hla_swd" -f target/stm32f4x.cfg -c "program {$(BUILD_DIR)/$(TARGET).elf}  verify reset; shutdown;"

clean:
	rm -rf $(BUILD_DIR)
