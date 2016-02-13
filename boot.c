#include "boot.h"
#include "subr.h"

extern void *__bss_start;
extern void *__bss_end__;
uint8_t __stack[512] __attribute__((aligned(4), section(".stack")));

void kern_boot(void);
void _start(void) __attribute__ ( ( naked ) );

const char *msg = "Hello world!\n";
int myvar = 16;
int foo;

/*
int
task(void) {

	return 0;
}
*/

void
clearbss(void)
{
	unsigned int *start = (unsigned int *)&__bss_start;
	unsigned int *end = (unsigned int *)&__bss_end__;
	unsigned int *p;

	for (p = start; p < end; p++)
		*p = 0x00;
}

void
testargs(const char *s, int *a)
{
	const char *p;
	int *p1;

	p = s;
	p1 = a;
}

void
_start(void)
{

	asm volatile("ldr sp, =0x80200");

	clearbss();

	kern_boot();
}

void
kern_boot(void)
{
	//testargs("hello", &myvar);
	*uart_base = (int)'H';

	/* Loop forever */
	//kprintf("Hello");
	for(;;);
}
