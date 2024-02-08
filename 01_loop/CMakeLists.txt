cmake_minimum_required(VERSION 3.25)

project(01_loop LANGUAGES ASM C)

set(CMAKE_ASM_COMPILER	"arm-none-eabi-gcc")
set(CMAKE_LINKER		"arm-none-eabi-ld")
set(OBJCOPY				"arm-none-eabi-objcopy")
set(OBJDUMP				"arm-none-eabi-objdump")

# add_compile_options(-mcpu=cortex-m3 -mthumb -Wall -std=gnu99)
add_compile_options(-mcpu=cortex-m3 -mthumb -Wall)
set(FNAME loop)
add_subdirectory(src)