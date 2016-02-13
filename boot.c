#include "boot.h"
#include "subr.h"

extern void *__bss_start;
extern void *__bss_end__;
extern void *_stack;

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
		*p = 0x0;
}

void
testargs(const char *s, int *a)
{
	const char *p;
	int *p1;

	p = s;
	p1 = a;
}


int _start(void)
{

	clearbss();
	testargs("hello", &myvar);
	*uart_base = (int)'H';

	/* Loop forever */
	for(;;);

  return 0;
}
