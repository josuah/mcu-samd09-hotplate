MEMORY {
	ROM (rx) : ORIGIN = 0x00000000, LENGTH = 16K
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 4K
}

ENTRY(__reset_handler)

SECTIONS {
	.text : {
		KEEP(*(.data.__stack_pointer))
		KEEP(*(.data.__vectors))
		. = ALIGN(4);
		*(.text .text.*)
		*(.rodata .rodata.*)
	} > ROM

	.data : {
		PROVIDE(__data_start = .);
		*(.data .data.*)
		PROVIDE(__data_end = .);
	} > RAM AT> ROM

	.bss ADDR(.data) + SIZEOF (.data) : AT (ADDR (.bss)) {
		PROVIDE(__bss_start = .);
		*(.bss .bss.*)
		PROVIDE(__bss_end = .);
	} > RAM

	__data_load_start = LOADADDR(.data);
	__data_load_end = __data_load_start + SIZEOF(.data);
	__stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
