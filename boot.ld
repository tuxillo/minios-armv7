ENTRY(_startup)
SECTIONS
{
	. = 0x100000;
	.text : { startup.o *(.text) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	.bss : { *(.bss*) *(COMMON) }
	. = . + 0x1000; /* 4kB of stack memory */
	stack_top = .;
}
