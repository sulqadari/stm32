add_executable(${FNAME}.elf "")

target_sources(${FNAME}.elf
	PRIVATE
	loop.s
)

target_link_options(${FNAME}.elf
	PUBLIC
	-T ${CMAKE_CURRENT_SOURCE_DIR}/loop.ld
	-nostdlib
	-nostartfiles
)

add_custom_command(TARGET ${FNAME}.elf
	POST_BUILD
	COMMAND ${OBJCOPY} -O binary ${FNAME}.elf ${FNAME}.bin
	BYPRODUCTS ${FNAME}.bin
)

add_custom_command(TARGET ${FNAME}.elf
	POST_BUILD
	COMMAND ${OBJCOPY} -O ihex ${FNAME}.elf ${FNAME}.hex
	BYPRODUCTS ${FNAME}.hex
)