ENTRY(_reset)
SECTIONS
{

	 . = 0x8000;
	.text :
	{
	      *(.text.boot)
	      *(.text)
	}
	.rodata :
	{
		*(.rodata)
	}
	.data :
	{
		*(.data)
	}
	.bss :
	{
	     __bss_start = .;
	     *(.sbss.*)
	     *(.bss*)
	     *(COMMON)
	     __bss_end = .;
	}
	. = . + 0x1000; /* 4kB for stack */
	stack_top = .;
}
