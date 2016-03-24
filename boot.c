/*
 * Copyright (c) 2016, Antonio Huete Jimenez <tuxillo@quantumachine.net>
 * All rights reserved.
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

#include <types.h>
#include <subr.h>
#include <cpufunc.h>
#include <syscalls.h>
#include <thread.h>
#include <uart.h>
#include <bcm2836.h>

extern unsigned int *__bss_start;
extern unsigned int *__bss_end;

void kern_boot(void);
void clearbss(void);
void usermode(void);

static void
DELAY(uint32_t usec)
{
       int counts;
       for (; usec > 0; usec--)
               for (counts = 200; counts > 0; counts--)
                       ;
}

void clearbss(void)
{
	unsigned int *start = (unsigned int *)&__bss_start;
	unsigned int *end = (unsigned int *)&__bss_end;
	unsigned int *p;

	/* Not efficient */
	for (p = start; p < end; p++)
		*p = 0x00;

}

static void
minios_startup_msg(void)
{
	kprintf("miniOS ARMv7-%s startup ...\n", MINIOS_VERSION);
}

void
kern_boot(void)
{
	minios_startup_msg();

	/* Startup */
	clearbss();

	/* Initialize UART */
	uart_pl011_init(115200, 8, 1, 0);

	bcm2836_core_timer(0, CNTPSIRQ);
	enable_irq();

	cp15_cntp_tval_set(0x20ce700);
	cp15_cntp_ctl_set(1);
	kprintf("cp15_cntp_ctl_get: 0x%x\n", cp15_cntp_ctl_get());

	/* Loop forever */
	for (;;);
}
