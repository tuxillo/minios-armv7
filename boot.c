#include "boot.h"
#include "subr.h"

void kern_boot(void);

char *msg = "Hello world!\n";
int myvar = 16;

void
testargs(char *s, int *a)
{
	const char *p;
	int *p1;

	p = s;
	if (s == NULL)
		*uart_base = (int)'0';
	else
		*uart_base = (int)'1';

	p1 = a;
}


void
kern_boot(void)
{
	testargs(msg, &myvar);

	/* Loop forever */
	for(;;);
}
