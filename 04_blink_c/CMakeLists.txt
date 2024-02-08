cmake_minimum_required(VERSION 3.25)

project(04_blink LANGUAGES ASM C)

set(CMAKE_C_COMPILER	"arm-none-eabi-gcc")
set(CMAKE_ASM_COMPILER	"arm-none-eabi-gcc")
set(CMAKE_LINKER		"arm-none-eabi-ld")
set(OBJCOPY				"arm-none-eabi-objcopy")
set(OBJDUMP				"arm-none-eabi-objdump")


# add_compile_options(-mcpu=cortex-m3 -mthumb -Wall)

add_compile_options(
	-std=gnu99 -mcpu=cortex-m0 -mthumb -D__MICROLIB
	-D__thumb2__=1 -DMH1701 -D__CORTEX_M0
	-mtune=cortex-m0 -mapcs-frame -msoft-float
	-fdata-sections -ffunction-sections -fno-hosted
	-fno-builtin  -nostdlib -nodefaultlibs
	-Xlinker --gc-sections
)

set(FNAME loop)
add_subdirectory(src)