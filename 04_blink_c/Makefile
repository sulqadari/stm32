BUILD_DIR	= ./build
OBJCOPY		= arm-none-eabi-objcopy
LINKER		= arm-none-eabi-ld
ASM			= arm-none-eabi-as
COMPILER	= arm-none-eabi-gcc

all: blink.bin

blink.bin: blink.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/blink.elf $(BUILD_DIR)/blink.bin

blink.elf: linker.ld reset_exception_handler.o blink.o
	$(LINKER) -T linker.ld -o $(BUILD_DIR)/blink.elf reset_exception_handler.o blink.o

reset_exception_handler.o: reset_exception_handler.s
	$(ASM) -o reset_exception_handler.o reset_exception_handler.s

blink.o: blink.c
	$(COMPILER) -mcpu=cortex-m3 -g -O3 -c -o blink.o blink.c

flash: blink.bin
	st-flash --connect-under-reset write $(BUILD_DIR)/blink.bin 0x08000000

clean:
	rm -f blink.o $(BUILD_DIR)/blink.elf $(BUILD_DIR)/blink.bin
	rm -f reset_exception_handler.o blink.o
