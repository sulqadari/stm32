/*
	0. the 'flash' section begins at address 0x08000000.
	1. at address 0x08000000 we keep the 'sp' initial offset. This offset
	   equals to 0x20005000.
	2. at address 0x08000004 we keep the 'pc' initial offset. Right now
	   it isn't calculated yet.
	3. advance the section's pointer to 0x130 bytes. Now the current address
	   is 0x08000130.
	4. from loop.o object file export 'code' section and expose it at
	   address 0x08000130. No that the linker knows its address, it will
	   implicitly 'patch' the value at address 0x08000004.
*/
SECTIONS {
	flash 0x08000000 : {
		LONG(0x20000000 + 20K);
		LONG(_reset_exception_handler | 1);
		. = 0x130;
		./build/loop.o(text);
	}
}