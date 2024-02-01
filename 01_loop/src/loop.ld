SECTIONS {
	flash 0x08000000 : {
		LONG(0x20000000 + 20K);
		LONG(loop | 1);
		. = 0x130;
		loop.o(code);
	}
}