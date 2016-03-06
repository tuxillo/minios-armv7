/*
 * Copyright (c) 2015 The FreeBSD Foundation
 * Copyright (c) 2016, Antonio Huete Jimenez <tuxillo@quantumachine.net>
 * All rights reserved.
 *
 * This software was developed by Konstantin Belousov
 * under sponsorship from the FreeBSD Foundation.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES ;
 * LOSS OF USE, DATA, OR PROFITS ; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the author.
 */

#ifndef _CPUFUNC_H_
#define _CPUFUNC_H_

#include <types.h>

#define isb()  __asm __volatile("mcr p15, 0, %0, c7, c5, 4" : : "r" (0) : "memory")

static __inline register_t
cp15_cntfrq_get(void)
{
	register_t reg;

	__asm __volatile("mrc p15, 0, %0, c14, c0, 0" : "=r" (reg));

	return reg;
}

static __inline uint64_t
cp15_cntpct_get(void)
{
	uint64_t reg;

	__asm __volatile("mrrc\tp15, 0, %Q0, %R0, c14" : "=r" (reg));

	return reg;
}

static inline uint64_t
cp15_cntvct_get(void)
{
	uint64_t reg;

	__asm __volatile("mrrc\tp15, 1, %Q0, %R0, c14" : "=r" (reg));
	return (reg);
}

static __inline void
cp15_cntp_ctl_set(register_t reg)
{
	__asm __volatile("mcr p15, 0, %0, c14, c2, 1" :: "r" (reg));
}

static __inline void
cp15_cntv_ctl_set(register_t reg)
{
	__asm __volatile("mcr p15, 0, %0, c14, c3, 1" :: "r" (reg));
}

static __inline void
cp15_cntp_tval_set(register_t reg)
{
	__asm __volatile("mcr p15, 0, %0, c14, c2, 0" :: "r" (reg));
}

static __inline void
cp15_cntv_tval_set(register_t reg)
{
	__asm __volatile("mcr p15, 0, %0, c14, c3, 0" :: "r" (reg));
}

static __inline register_t
cp15_cntp_ctl_get(void)
{
	register_t reg;

	__asm __volatile("mrc p15, 0, %0, c14, c2, 1" : "=r" (reg));

	return reg;
}

static __inline register_t
cp15_cntv_ctl_get(void)
{
	register_t reg;

	__asm __volatile("mrc p15, 0, %0, c14, c3, 1" : "=r" (reg));

	return reg;
}

static __inline register_t
cp15_cntkctl_get(void)
{
	register_t reg;

	__asm __volatile("mrc p15, 0, %0, c14, c1, 0" : "=r" (reg));

	return reg;
}

static __inline void
cp15_cntkctl_set(register_t reg)
{
	__asm __volatile("mcr p15, 0, %0, c14, c1, 0" :: "r" (reg));
}

static __inline void
enable_irq(void)
{
	__asm __volatile("cpsie i" ::);
}

static __inline void
enable_fiq(void)
{
	__asm __volatile("cpsie f" ::);
}

static __inline register_t
_read_cpsr(void)
{
	uint32_t r;

	__asm __volatile("mrs %0, cpsr" : "=r" (r));

	return r;
}

static __inline void
syscall_entry(int syscall, void *arg)
{
	__asm __volatile("svc #0x0");
}

#endif /* _CPUFUNC_H_ */
