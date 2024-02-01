BUILD_DIR	= ../build
OBJCOPY		= arm-none-eabi-objcopy
LINKER		= arm-none-eabi-ld
ASM			= arm-none-eabi-as

loop.bin: loop.elf
	$(OBJCOPY) -O binary -j flash $(BUILD_DIR)/loop.elf $(BUILD_DIR)/loop.bin

loop.elf: loop.ld loop.o
	$(LINKER) -T loop.ld -o $(BUILD_DIR)/loop.elf loop.o

loop.o: loop.s
	$(ASM) -o loop.o loop.s

clean:
	rm -f loop.o $(BUILD_DIR)/loop.elf $(BUILD_DIR)/loop.bin