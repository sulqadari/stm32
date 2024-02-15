add_executable(${FNAME}.elf
	main.c
	${CMSIS_TEMPLATES}/system_stm32f1xx.c
	${CMSIS_TEMPLATES}/gcc/startup_stm32f103xb.s
)

target_include_directories(${FNAME}.elf PUBLIC
	${CMSIS_INCLUDE}
	${CMSIS_DEVICE}
)

add_compile_options(-mcpu=cortex-m3 -g -O0 -std=c17 -Wall -Wextra -Wpedantic)
add_compile_definitions(STM32F103xB)
target_link_options(${FNAME}.elf
	PUBLIC -T ${PROJECT_SOURCE_DIR}/src/STM32F103XB_FLASH.ld
	PUBLIC -nostdlib
)

add_custom_command(OUTPUT ${FNAME}.bin
	COMMENT "Generating ${FNAME}.bin..."
	COMMAND arm-none-eabi-objcopy -O binary ${FNAME}.elf
)