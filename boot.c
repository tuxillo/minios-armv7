#include <types.h>
#include <subr.h>
#include <cpufunc.h>

void kern_boot(void);
void clearbss(int);

void clearbss(int show)
{
	extern unsigned int *__bss_start;
	extern unsigned int *__bss_end;
	unsigned int *start, *end, *p;

	for (p = start; p < end; p++) {
		if (show)
			kprintf("0x%x ", *p);
		*p = 0x00;
	}
	kprintf("\n");
}

void
kern_boot(void)
{

	kprintf("miniOS arvm7 startup ...\n");

	/* Startup */
	kprintf("Clearing bss section");
	clearbss(TRUE);

	kprintf("cpsr=0x%x\n", _read_cpsr());

	/* Loop forever */
	for(;;);
}
