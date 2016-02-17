ENTRY(_startup)
SECTIONS
{

	/*
	 * For qemu -M virt memory starts at 0x40000000.
	 * More details on hw/arm/virt.c file of qemu.
	 */
	 . = 0x40000000;
	.text :
	{
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
