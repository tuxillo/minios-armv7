ENTRY(_reset)
SECTIONS
{

	 . = 0x8000;
	.text :
	{
	      *(.text.boot)
	      *(.text)
	}
	. = ALIGN(4);

	.rodata :
	{
		*(.rodata)
	}
	. = ALIGN(4);

	.data :
	{
		*(.data)
	}
	. = ALIGN(4);

	.bss :
	{
	     __bss_start = .;
	     *(.sbss.*)
	     *(.bss*)
	     *(COMMON)
	     __bss_end = .;
	}
	. = ALIGN(4);

	kernstack_base = .;
	. = . + 0x1000; /* 4kB for kernel stack */
	kernstack_top = .;
	. = ALIGN(4);

	usrstack_base = .;
	. = . + 0x1000; /* 4kB for userland stack */
	usrstack_top = .;
	. = ALIGN(4);
}
