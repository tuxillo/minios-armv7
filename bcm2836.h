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

#ifndef _BCM2836_H_
#define _BCM2836_H_

/* Interrupt controller */
struct bcm2836_intc {
	uint32_t irq_basic_pending;
	uint32_t irq_1_pending;
	uint32_t irq_2_pending;
	uint32_t fiq_control;
	uint32_t irq_1_enable;
	uint32_t irq_2_enable;
	uint32_t irq_basic_enable;
	uint32_t irq_1_disable;
	uint32_t irq_2_disable;
	uint32_t irq_basic_disable;
};

extern volatile struct bcm2836_intc *bcm2836_intc;

/* BCM2836 (Raspberry 2) addresses */
#define BCM2836_PERIPH_BASE	0x3f000000
#define BMC2836_UART0	(BCM2836_PERIPH_BASE + 0x00201000)

#define BCM2836_LOCAL_TIMER_FREQ	19200000

#define BCM2836_INTC_BASE		0x3f00b000

#define BCM2836_LOCAL_PERIPH_BASE	0x40000000

#define BCM2836_LOCAL_CTL_BASE		(BCM2836_LOCAL_PERIPH_BASE + 0x0000)
#define BCM2836_CORE_TIMER_PRESCALER	(BCM2836_LOCAL_PERIPH_BASE + 0x0008)
#define BCM2836_GPU_INT_ROUTING		(BCM2836_LOCAL_PERIPH_BASE + 0x000c)
#define BCM2836_CORE_TIMER_LS32		(BCM2836_LOCAL_PERIPH_BASE + 0x001c)
#define BCM2836_CORE_TIMER_MS32		(BCM2836_LOCAL_PERIPH_BASE + 0x0020)
#define BCM2836_LOCAL_INT_ROUTING	(BCM2836_LOCAL_PERIPH_BASE + 0x0024)
#define BCM2836_LOCAL_TIMER_CTL		(BCM2836_LOCAL_PERIPH_BASE + 0x0034)
#define BCM2836_LOCAL_TIMER_WFLAGS	(BCM2836_LOCAL_PERIPH_BASE + 0x0038)

#define BCM2836_CORE_INT_CTL(cpu)	((BCM2836_LOCAL_PERIPH_BASE + 0x0040) + (cpu * 4))

#define CNTPSIRQ	0x1
#define CNTPNSIRQ	0x2
#define CNTPHIRQ	0x4
#define CNTPVIRQ	0x8
#define CNTPSFIQ	0x10
#define CNTPNSFIQ	0x20
#define CNTPHFIQ	0x40
#define CNTPVFIQ	0x80

/* Prototypes */
void bcm2836_intc_print(void);
void bcm2836_core_timer(int, uint32_t);

#endif /* _BCM2836_H_ */
