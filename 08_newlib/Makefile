# Note: before executing this Makefile pass in the following command:
# $ export CMSIS_STM32F1=/home/telman/work/STM32CubeF1/Drivers/CMSIS

CMSIS_STM32F1	:= /home/telman/develop/STM32_assembly/07_cmsis/CMSIS
CMSIS_TEMPLATES := $(CMSIS_STM32F1)/Device/ST/STM32F1xx/Source/Templates
CMSIS_SYSTEM	:= $(CMSIS_TEMPLATES)/system_stm32f1xx.c
CMSIS_STARTUP	:= $(CMSIS_TEMPLATES)/gcc/startup_stm32f103xb.s

CPPFLAGS	:= -I$(CMSIS_STM32F1)/Device/ST/STM32F1xx/Include
CPPFLAGS	+= -I$(CMSIS_STM32F1)/Include
CPPFLAGS	+= -DSTM32F103xB

# -ffunction-sections -fdata-sections forces compiler to create separate sections for functions and data in outgoing elf-file.
CFLAGS		:= -mcpu=cortex-m3 -g -std=c17 -Wall -Wextra -Wpedantic -ffunction-sections -fdata-sections
CFLAGS		+= -O0
LDSCRIPT	:= STM32F103XB_FLASH.ld
LDFLAGS		:= -Wl,-T,$(LDSCRIPT) -Wl,--gc-sections

AS		:= arm-none-eabi-as
CC		:= arm-none-eabi-gcc
LD		:= arm-none-eabi-ld
OBJCOPY	:= arm-none-eabi-objcopy

uarts.bin: uarts.elf
	$(OBJCOPY) -O binary ./build/$< ./build/$@

uarts.elf: startup_stm32f103xb.o system_stm32f1xx.o main.o
	$(CC) -o ./build/$@ $(CFLAGS) $(LDFLAGS) ./build/startup_stm32f103xb.o ./build/system_stm32f1xx.o ./build/main.o

startup_stm32f103xb.o: $(CMSIS_STARTUP)
	@rm -rf build > /dev/null
	@mkdir build
	$(AS) -o ./build/$@ $<

system_stm32f1xx.o: $(CMSIS_SYSTEM)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o ./build/$@ $<

main.o: main.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o ./build/$@ $<

flash: uarts.bin
	st-flash --connect-under-reset write $< 0x08000000

clean:
	rm -f ./build/uarts.elf ./build/uarts.bin ./build/*.o