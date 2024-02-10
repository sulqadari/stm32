BUILD_DIR	= ./build
SRC_DIR		= ./src
OBJCOPY		= arm-none-eabi-objcopy
LINKER		= arm-none-eabi-ld
ASM			= arm-none-eabi-as
COMPILER	= arm-none-eabi-gcc

all: blink.bin

blink.bin: blink.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/blink.elf $(BUILD_DIR)/blink.bin

blink.elf: $(SRC_DIR)/linker.ld reset_exception_handler.o blink.o
	$(LINKER) -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/blink.elf $(BUILD_DIR)/reset_exception_handler.o $(BUILD_DIR)/blink.o

reset_exception_handler.o: $(SRC_DIR)/reset_exception_handler.s
	$(ASM) -o $(BUILD_DIR)/reset_exception_handler.o $(SRC_DIR)/reset_exception_handler.s

blink.o: $(SRC_DIR)/blink.c
	$(COMPILER) -mcpu=cortex-m3 -g -O3 -c -o $(BUILD_DIR)/blink.o $(SRC_DIR)/blink.c

flash: blink.bin
	st-flash --connect-under-reset write $(BUILD_DIR)/blink.bin 0x08000000

clean:
	rm -f blink.o $(BUILD_DIR)/blink.elf $(BUILD_DIR)/blink.bin
	rm -f reset_exception_handler.o blink.o
