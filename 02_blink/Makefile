BUILD_DIR	= ./build
OBJCOPY		= arm-none-eabi-objcopy
LINKER		= arm-none-eabi-ld
ASM			= arm-none-eabi-as

all: blink.bin

blink.bin:  blink.elf
	$(OBJCOPY) -O binary -j flash $(BUILD_DIR)/blink.elf $(BUILD_DIR)/blink.bin

blink.elf: blink.ld blink.o
	$(LINKER) -T blink.ld -o $(BUILD_DIR)/blink.elf blink.o

blink.o: blink.s
	$(ASM) -o blink.o blink.s

flash: blink.bin
	st-flash write --connect-under-reset $(BUILD_DIR)/blink.bin 0x08000000

clean:
	rm -f blink.o $(BUILD_DIR)/blink.elf $(BUILD_DIR)/blink.bin