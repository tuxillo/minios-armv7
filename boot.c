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

int
proc1(void *arg)
{
	for(;;) {
		kprintf("[usr] running process 1\n");
		syscall_entry(SYS_YIELD, NULL);
		DELAY(1000000);
		kprintf("[usr] again process 1\n");
	}
	return 0;
}

int
proc2(void *arg)
{
	for(;;) {
		kprintf("[usr] running process 2\n");
		syscall_entry(SYS_YIELD, NULL);
		DELAY(1000000);
		kprintf("[usr] again process 2\n");
	}
	return 0;
}

void
kern_boot(void)
{
	int cnt = 0;
	volatile register_t *irq_1 = (volatile register_t *)0x3f00b210;
	volatile register_t *irq_2 = (volatile register_t *)0x3f00b214;
	volatile register_t *irq_basic = (volatile register_t *)0x3f00b218;
	volatile register_t *core0_irq = (volatile register_t *)0x40000040;
	volatile register_t *core1_irq = (volatile register_t *)0x40000044;
	volatile register_t *core2_irq = (volatile register_t *)0x40000048;
	volatile register_t *core3_irq = (volatile register_t *)0x4000004c;
	volatile register_t *prescaler = (volatile register_t *)0x4000008;
	volatile register_t *core_tr1 = (volatile register_t *)0x400001c;
	volatile register_t *core_tr2 = (volatile register_t *)0x4000020;
	volatile register_t *core0_source = (volatile register_t *)0x40000060;

	int i = 0;

	kprintf("miniOS ARMv7 startup ...\n");

	/* Startup */
	clearbss();

	/* Initialize UART */
	uart_pl011_init(115200, 8, 1, 0);

	thread_create(proc1);
	thread_create(proc2);

	*prescaler = 0x2;

	kprintf("prescaler=0x%x tr1=0x%x tr2=0x%x\n", *prescaler, *core_tr1, *core_tr2);

	*core0_irq = 0x3;

	enable_irq();

	bcm2836_intc_print();

	kprintf("core0 int control 0x%x 0x%x\n", *core0_irq, *core0_source);

	cp15_cntp_tval_set(0x20ce700);
	cp15_cntp_ctl_set(1);
	kprintf("cp15_cntp_ctl_get: 0x%x\n", cp15_cntp_ctl_get());

//	while((cp15_cntp_ctl_get() & (1<<2)) == 0)
//		kprintf(".");

	kprintf("Alarm! Wake up %x\n");

	/* Run all user mode threads */
	//run_threads();

	/* Loop forever */
	for (;;);
}
