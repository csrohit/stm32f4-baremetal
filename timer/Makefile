TARGET = timer

LDSCRIPT    = stm32f4.ld

PREFIX      = arm-none-eabi
CC          = ${PREFIX}-gcc
LD          = ${PREFIX}-ld
AS          = ${PREFIX}-as
GDB         = ${PREFIX}-gdb
OBJCOPY     = ${PREFIX}-objcopy
SIZE        = ${PREFIX}-size

SRC_DIRS    = src
BUILD_DIR   = build
INC_DIRS    = include /opt/arm-gnu-toolchain/arm-none-eabi/include
DEFS        = -DSTM32F401xC

MCU_FLAGS   = -mcpu=cortex-m4 -mfloat-abi=soft -mthumb -g -gdwarf-2
INCFLAGS    = $(addprefix -I,$(INC_DIRS))
LDFLAGS     = $(MCU_FLAGS) $(INCFLAGS) -nostdlib
CFLAGS      = $(INCFLAGS) $(MCU_FLAGS) -nostdlib
CPPFLAGS    = $(INCFLAGS) $(DEFS)

SRCS        = $(shell find $(SRC_DIRS) -name '*.c')
OBJS        = $(SRCS:%.c=$(BUILD_DIR)/%.o)

all : bin size
elf : $(BUILD_DIR)/$(TARGET).elf
bin : $(BUILD_DIR)/$(TARGET).bin
size: $(BUILD_DIR)/$(TARGET).size

%.bin: %.elf
	$(OBJCOPY) -Obinary $(*).elf $(*).bin

%.size: %.elf
	$(SIZE) $<

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ $(OBJS) -T$(LDSCRIPT) -Wl,-Map="$(BUILD_DIR)/$(TARGET).map"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

flash_stlink: bin
	st-flash --connect-under-reset write $(TARGET).bin 0x8000000

flash: elf
	STM32_Programmer_CLI -c port=SWD ap=0 -w $(BUILD_DIR)/$(TARGET).elf -rst

erase:
	STM32_Programmer_CLI -c port=SWD ap=0 -e all

reset:
	STM32_Programmer_CLI -c port=SWD ap=0 -rst

clean:
	rm -rf $(BUILD_DIR)
