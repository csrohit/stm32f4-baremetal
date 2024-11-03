TARGET = tim1

LDSCRIPT 	= stm32f4.ld

PREFIX      =   arm-none-eabi
CC          =   ${PREFIX}-gcc
LD 		    =   ${PREFIX}-ld
AS 		    =   ${PREFIX}-as
GDB 	    =   ${PREFIX}-gdb
OBJCOPY     =   ${PREFIX}-objcopy
SIZE     	=   ${PREFIX}-size

SRC_DIRS    = src
BUILD_DIR   = build
INC_DIRS	= include
DEFS 		= -DSTM32F401xE

MCU_FLAGS 	= -mcpu=cortex-m4 -mfloat-abi=soft -mthumb -g -gdwarf-2
LDFLAGS     = $(MCU_FLAGS) -nostdlib 
CFLAGS      = $(MCU_FLAGS) -nostdlib
CPPFLAGS 	= $(addprefix -I,$(INC_DIRS)) $(DEFS)

SRCS        = $(shell find $(SRC_DIRS) -name '*.c')
OBJS        = $(SRCS:%.c=$(BUILD_DIR)/%.o) 

all : elf size
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

flash: bin
	STM32_Programmer_CLI -c port=SWD ap=0 -w $(BUILD_DIR)/$(TARGET).elf -rst
	# st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000

clean:
	rm -rf $(BUILD_DIR)
