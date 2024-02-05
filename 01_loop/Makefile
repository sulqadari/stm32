BUILD_DIR	= ./build
SRC_DIR		= ./src
OBJCOPY		= arm-none-eabi-objcopy
LINKER		= arm-none-eabi-ld
ASM			= arm-none-eabi-as

all: loop.bin

loop.bin: loop.elf
	$(OBJCOPY) -O binary -j flash $(BUILD_DIR)/loop.elf $(BUILD_DIR)/loop.bin

loop.elf: $(SRC_DIR)/loop_make.ld loop.o
	$(LINKER) -T $(SRC_DIR)/loop_make.ld -o $(BUILD_DIR)/loop.elf $(BUILD_DIR)/loop.o

loop.o: $(SRC_DIR)/loop.s
	$(ASM) -o $(BUILD_DIR)/loop.o $(SRC_DIR)/loop.s

clean:
	rm -f $(BUILD_DIR)/loop.o $(BUILD_DIR)/loop.elf $(BUILD_DIR)/loop.bin

.PHONY: all