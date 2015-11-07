#ifndef _BOOT_H_
#define _BOOT_H_

extern volatile unsigned int * const uart_base;

void _pc(int, void *);
//ssize_t _write(int, const void *, size_t);
	
#endif /* _BOOT_H_ */
