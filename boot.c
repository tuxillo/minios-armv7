#include "boot.h"
#include "subr.h"

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
testargs(const char *s, int *a)
{
	const char *p;
	int *p1;

	p = s;
	p1 = a;
}


int _start(void)
{

  _pc('h', NULL);
  _pc('\n', NULL);
  _pc('e', NULL);
  _pc('\n', NULL);
  _pc('l', NULL);
  _pc('\n', NULL);
  _pc('l', NULL);
  _pc('\n', NULL);
  _pc('o', NULL);
  _pc('\n', NULL);

  testargs(msg, &myvar);
//  kprintf("%s", msg);

  /* Loop forever */
  for(;;);

  return 0;
}
