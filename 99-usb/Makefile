CMSIS       ?= CMSIS
CMSISDEV    ?= $(CMSIS)/Device
CMSISCORE   ?= $(CMSIS)/CMSIS/Include $(CMSIS)/CMSIS/Core/Include
FLASH       ?= st-flash
TOOLSET     ?= arm-none-eabi-
CC           = $(TOOLSET)gcc
LD           = $(TOOLSET)gcc
AR           = $(TOOLSET)gcc-ar
OBJCOPY      = $(TOOLSET)objcopy
DFU_UTIL    ?= dfu-util
STPROG_CLI  ?= ~/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI
OPTFLAGS    ?= -Os

ifeq ($(OS),Windows_NT)
	RM = del /Q
	fixpath = $(strip $(subst /,\, $1))
else
	RM = rm -f
	fixpath = $(strip $1)
endif

MODULE      ?= libusb.a
CFLAGS      ?= -mcpu=cortex-m3
DEFINES     ?= STM32F1 STM32F103x6 CDC_USE_IRQ

ARFLAGS      = -cvq
LDFLAGS      = --specs=nano.specs -nostartfiles -Wl,--gc-sections -L demo
INCLUDES     = $(CMSISDEV)/ST $(CMSISCORE) inc
CFLAGS2     ?= $(CFLAGS) -mthumb -std=gnu99 $(OPTFLAGS)

OBJDIR       = obj
SOURCES      = $(wildcard src/*.c) $(wildcard src/*.S)
OBJECTS      = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(notdir $(basename $(SOURCES)))))
DSRC         = $(wildcard demo/*.c) $(wildcard demo/*.S) $(STARTUP)
DOBJ         = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(notdir $(basename $(DSRC)))))
DOUT         = cdc_loop

SRCPATH      = $(sort $(dir $(SOURCES) $(DSRC)))
vpath %.c $(SRCPATH)
vpath %.S $(SRCPATH)
vpath %.s $(SRCPATH)

help all:
	@echo 'Usage: make target [program]'
	@echo 'Available targets are:'
	@echo '  bluepill'
	@echo '  stm32f103x6   CDC loopback demo for STM32F103 based boards'
	@echo '  32l100c-disco'
	@echo '  stm32l100xc   CDC loopback demo for STM32L100xC based boards'
	@echo '  32l476rg-nucleo'
	@echo '  stm32l476rg   CDC loopback demo for STM32L476xG based boards'
	@echo '  stm32l052x8   CDC loopback demo for STM32L052x8 based boards'
	@echo '  32f429zi-nucleo'
	@echo '  stm32f429xi   CDC loopback demo for STM32F429xI based boards'
	@echo '  stm32f401xc   CDC loopback demo for STM32F401xC based boards'
	@echo '  stm32f401xe   CDC loopback demo for STM32F401xE based boards'
	@echo '  cmsis         Download CMSIS 5 and stm32.h into a $$(CMSIS) directory'
	@echo '  doc           DOXYGEN documentation'
	@echo '  module        static library module using following envars (defaults)'
	@echo '                MODULE  module name ($(MODULE))'
	@echo '                CFLAGS  mcu specified compiler flags ($(CFLAGS))'
	@echo '                DEFINES mcu and module specified defines ($(DEFINES))'
	@echo '                        see USB Device HW driver and core API section for the'
	@echo '                        compile-time control macros'
	@echo ' '
	@echo 'Environmental variables (defaults):'
	@echo '  CMSIS         Path to the CMSIS V4 or CMSIS V5 root folder ($(CMSIS))'
	@echo '  CMSISCORE     Path to the CMSIS Core include folder(s) ($(CMSISCORE))'
	@echo '  CMSISDEV      Path to the CMSIS Device folder ($(CMSISDEV))'
	@echo '  FLASH         st-link flash utility ($(FLASH))'
	@echo ' '
	@echo 'Examples:'
	@echo '  make bluepill program'
	@echo '  make module MODULE="usbd.a" CFLAGS="-mcpu=cortex-m4" DEFINES="STM32L4 STM32L476xx USBD_VBUS_DETECT"'

cmsis: $(CMSISDEV)/ST

$(CMSISDEV)/ST: $(CMSIS)
	@git clone --recurse-submodules --depth 1 https://github.com/dmitrystu/stm32h.git $@

$(CMSIS):
	@git clone --depth 1 https://github.com/ARM-software/CMSIS_5.git $@

$(OBJDIR):
	@mkdir $@

program: $(DOUT).hex
	$(FLASH) --reset --format ihex write $(DOUT).hex

program_dfu: $(DOUT).bin
	$(DFU_UTIL) -d 0483:DF11 -a 0 -D $(DOUT).bin -s 0x08000000

program_stcube: $(DOUT).hex
	$(STPROG_CLI) -c port=SWD reset=HWrst -d $(DOUT).hex -hardRst

demo: $(DOUT).hex $(DOUT).bin

$(DOUT).bin : $(DOUT).elf
	@echo building $@
	@$(OBJCOPY) -O binary $< $@

$(DOUT).hex : $(DOUT).elf
	@echo building $@
	@$(OBJCOPY) -O ihex $< $@

$(DOUT).elf : $(OBJDIR) $(DOBJ) $(OBJECTS)
	@echo building $@
	@$(LD) $(CFLAGS2) $(LDFLAGS) -Wl,--script='$(LDSCRIPT)' -Wl,-Map=$(DOUT).map $(DOBJ) $(OBJECTS) -o $@

clean: $(OBJDIR)
	$(MAKE) --version
	@$(RM) $(DOUT).*
	@$(RM) $(call fixpath, $(OBJDIR)/*.*)

doc:
	doxygen

module: clean
	$(MAKE) $(MODULE)

$(MODULE): $(OBJDIR) $(OBJECTS)
	@$(AR) $(ARFLAGS) $(MODULE) $(OBJECTS)

$(OBJDIR)/%.o: %.c
	@echo compiling $<
	@$(CC) $(CFLAGS2) $(addprefix -D, $(DEFINES)) $(addprefix -I, $(INCLUDES)) -c $< -o $@

$(OBJDIR)/%.o: %.S
	@echo assembling $<
	@$(CC) $(CFLAGS2) $(addprefix -D, $(DEFINES)) $(addprefix -I, $(INCLUDES)) -c $< -o $@

$(OBJDIR)/%.o: %.s
	@echo assembling $<
	@$(CC) $(CFLAGS2) $(addprefix -D, $(DEFINES)) $(addprefix -I, $(INCLUDES)) -c $< -o $@

.PHONY: module doc demo clean program help all program_stcube cmsis

stm32f103x6 bluepill: clean
	@$(MAKE) demo STARTUP='$(CMSISDEV)/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103x6.s' \
						LDSCRIPT='demo/stm32f103x6.ld' \
						DEFINES='STM32F1 STM32F103x6 USBD_SOF_DISABLED' \
						CFLAGS='-mcpu=cortex-m3'

stm32f401xc: clean
	@$(MAKE) demo STARTUP='$(CMSISDEV)/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f401xc.s' \
						LDSCRIPT='demo/stm32f401xc.ld' \
						DEFINES='STM32F4 STM32F401xC USBD_SOF_DISABLED' \
						CFLAGS='-mcpu=cortex-m4'

stm32h743xx: clean
	@$(MAKE) demo STARTUP='$(CMSISDEV)/ST/STM32H7xx/Source/Templates/gcc/startup_stm32h743xx.s' \
						LDSCRIPT='demo/stm32h743xx.ld' \
						DEFINES='STM32H7 STM32H743xx USBD_VBUS_DETECT USBD_SOF_DISABLED' \
						CFLAGS='-mcpu=cortex-m7'

stm32f411xe stm32f411e-disco: clean
	@$(MAKE) demo STARTUP='$(CMSISDEV)/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f411xe.s' \
						LDSCRIPT='demo/stm32f401xe.ld' \
						DEFINES='STM32F4 STM32F411xE CDC_USE_IRQ' \
						CFLAGS='-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -g -gdwarf-2'
