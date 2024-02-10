MEMORY
{
	Flash : ORIGIN = 0x08000000, LENGTH = 64K
	SRAM  : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS {

	
	.isr_vector :
	{
		LONG(0X20000000 + 20K);
		/* '_reset_exception_handler' code shall initialize sections
		 * .bss, .data and proceed execution of func_start(). */
		. = 0x00000004;
		LONG(_reset_exception_handler | 1);
		. = 0x00000130;
	} > Flash

	.text :
	{
		. = ALIGN(4);
		*(.text)
		. = ALIGN(4);
	} > Flash

	.rodata :
	{
		. = ALIGN(4);
		*(.rodata)
		. = ALIGN(4);
	} > Flash

	.bss :
	{
		. = ALIGN(4);

		/* Define variable '_bss_start' with the value
		 * equal to current address, i.e. address of
		 * the beginning of output section. */
		_bss_start = .;

		/* Copy the .bss sections of all input files
		 * into output section. */
		*(.bss)
		. = ALIGN(4);
		_bss_end = .;
	
	/* '> SRAM' stands for "all symbols in .bss section shall
	 * point out to SRAM region. " */
	} > SRAM

	.data :
	{
		. = ALIGN(4);

		/* Define '_flash_data_start' and initialize it with
		 * the beginning address value of .data section in Flash. */
		_flash_data_start = LOADADDR(.data);

		/* Initialized with the beginning address of the '.data' section
		 * in SRAM. */
		_sram_data_start = .;
		*(.data)
		. = ALIGN(4);
		_sram_data_end = .;
	
	/*'> SRAM AT > Flash' stands for "this section resides in SRAM
	 * region, but shall be stored in Flash". */
	} > SRAM AT > Flash
}