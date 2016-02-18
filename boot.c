#include <types.h>
#include <subr.h>
#include <cpufunc.h>

int a;
int b;
int c;

extern unsigned int *__bss_start;
extern unsigned int *__bss_end;

void kern_boot(void);
void clearbss(void);

void clearbss(void)
{
	unsigned int *start = (unsigned int *)&__bss_start;
	unsigned int *end = (unsigned int *)&__bss_end;
	unsigned int *p;

	kprintf("clearing bss...");

	for (p = start; p < end; p++)
		*p = 0x00;

	kprintf("done\n");
}

void
kern_boot(void)
{

	kprintf("miniOS arvm7 startup ...\n");

	/* Startup */
	clearbss();

	/* Loop forever */
	for(;;);
}
