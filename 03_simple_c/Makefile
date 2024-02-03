BUILD_DIR	= ./build
OBJCOPY		= arm-none-eabi-objcopy
LINKER		= arm-none-eabi-ld
ASM			= arm-none-eabi-as
COMPILER	= arm-none-eabi-gcc

all: loop.bin

loop.bin: loop.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/loop.elf $(BUILD_DIR)/loop.bin

loop.elf: linker.ld reset_exception_handler.o loop.o
	$(LINKER) -T linker.ld -o $(BUILD_DIR)/loop.elf reset_exception_handler.o loop.o

reset_exception_handler.o: reset_exception_handler.s
	$(ASM) -o reset_exception_handler.o reset_exception_handler.s

loop.o: loop.c
	$(COMPILER) -mcpu=cortex-m3 -g -O0 -c -o loop.o loop.c

flash: loop.bin
	st-flash --connect-under-reset write $(BUILD_DIR)/loop.bin 0x08000000

clean:
	rm -f loop.o $(BUILD_DIR)/loop.elf $(BUILD_DIR)/loop.bin
	rm -f reset_exception_handler.o loop.o
