BUILD_DIR	= ./build
OBJCOPY		= arm-none-eabi-objcopy
LINKER		= arm-none-eabi-ld
ASM			= arm-none-eabi-as
COMPILER	= arm-none-eabi-gcc

all: usart.bin

usart.bin: usart.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/usart.elf $(BUILD_DIR)/usart.bin

usart.elf: linker.ld reset_exception_handler.o usart.o
	$(LINKER) -T linker.ld -o $(BUILD_DIR)/usart.elf reset_exception_handler.o usart.o

reset_exception_handler.o: reset_exception_handler.s
	$(ASM) -o reset_exception_handler.o reset_exception_handler.s

usart.o: usart.c
	$(COMPILER) -mcpu=cortex-m3 -g -O3 -c -o usart.o usart.c

flash: usart.bin
	st-flash --connect-under-reset write $(BUILD_DIR)/usart.bin 0x08000000

clean:
	rm -f usart.o $(BUILD_DIR)/usart.elf $(BUILD_DIR)/usart.bin
	rm -f reset_exception_handler.o usart.o
