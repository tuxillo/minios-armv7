#ifndef _CPUFUNC_H_
#define _CPUFUNC_H_

#include <types.h>

static __inline uint32_t
_read_cpsr(void)
{
	uint32_t r;

	__asm __volatile("mrs %0, cpsr" : "=r" (r));

	return r;
}

#endif /* _CPUFUNC_H_ */
