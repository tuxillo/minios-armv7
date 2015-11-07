#include <stdio.h>
#include "boot.h"

volatile unsigned int * const uart_base = (unsigned int *)0x09000000;

static
void
_pchar(char c)
{
	*uart_base = (unsigned int)c;
}


void _exit(int status)
{
}

int _close(int fd)
{
	return -1;
}

int
_isatty(void)
{
	return -1;

}

int _fstat(void)
{
	return -1;
}

int _lseek(void)
{
	return -1;
}

int _read(void)
{
	return -1;
}

ssize_t _write(int fd, const void *buf, size_t count)
{
	size_t total = 0;
	const char *b = (const char *)buf;
	int i;

	for (i = 0; *b != '\0' && i < count; i++, b++, total++)
		_pchar(*b);

	return total;
}

int _sbrk(void)
{
	return -1;
}
