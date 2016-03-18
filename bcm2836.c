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

/* Debug functions */

#include <types.h>
#include <subr.h>
#include <bcm2836.h>

/* Interrupt controller address */
volatile struct bcm2836_intc *bcm2836_intc =
	(volatile struct bcm2836_intc *)(BCM2836_INTC_BASE + 0x200);

static void
print_filtreg(uint32_t value)
{
	int bit;

	for (bit = 0; bit < 20; bit++) {
		if ((value & (1 << bit)) != 0)
			kprintf("%d:on ", bit);
	}
	kprintf("\n");
}

void
bcm2836_intc_print(void)
{

	kprintf("Basic Pending: %p 0x%x\n", &bcm2836_intc->irq_basic_pending,
		bcm2836_intc->irq_basic_pending);
	kprintf("Pending IRQ1 : %p 0x%x\n", &bcm2836_intc->irq_1_pending,
		bcm2836_intc->irq_1_pending);
	kprintf("Pending IRQ2 : %p 0x%x\n", &bcm2836_intc->irq_2_pending,
		bcm2836_intc->irq_2_pending);
	kprintf("Enable IRQ1  : %p 0x%x\n", &bcm2836_intc->irq_1_enable,
		bcm2836_intc->irq_1_enable);
	kprintf("Enable IRQ2  : %p 0x%x\n", &bcm2836_intc->irq_2_enable,
		bcm2836_intc->irq_2_enable);
	kprintf("Enable Basic : %p 0x%x\n", &bcm2836_intc->irq_basic_enable,
		bcm2836_intc->irq_basic_enable);
	kprintf("Disable IRQ1 : %p 0x%x\n", &bcm2836_intc->irq_1_disable,
		bcm2836_intc->irq_1_disable);
	kprintf("Disable IRQ2 : %p 0x%x\n", &bcm2836_intc->irq_2_disable,
		bcm2836_intc->irq_2_disable);
	kprintf("Disable Basic: %p 0x%x\n", &bcm2836_intc->irq_basic_disable,
		bcm2836_intc->irq_basic_disable);
}
