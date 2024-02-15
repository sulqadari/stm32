cmake_minimum_required(VERSION 3.25)
project(usart_timer LANGUAGES ASM C)
set(FNAME "Beacon")

set(CMAKE_C_COMPILER	"arm-none-eabi-gcc")
set(CMAKE_ASM_COMPILER	"arm-none-eabi-gcc")
set(CMAKE_LINKER		"arm-none-eabi-ld")
set(OBJCOPY				"arm-none-eabi-objcopy")
set(OBJDUMP				"arm-none-eabi-objdump")

set(CMSIS_STM32F1 "${PROJECT_SOURCE_DIR}/CMSIS")
set(CMSIS_TEMPLATES ${CMSIS_STM32F1}/Device/ST/STM32F1xx/Source/Templates)
set(CMSIS_INCLUDE ${CMSIS_STM32F1}/Include)
set(CMSIS_DEVICE ${CMSIS_STM32F1}/Device/ST/STM32F1xx/Include)

add_subdirectory(src)