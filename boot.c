#include <stdio.h>

volatile unsigned int * const uart_base = (unsigned int *)0x09000000;

int
task(void) {

	return 0;
}

void
print(char *s) {

  while (*s != '\0')
    *uart_base = (unsigned int)*s++;
}

void _start(void)
{
  char *msg = "Hello world!\n";

  print(msg);
}
