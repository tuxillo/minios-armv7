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

	.section .text.boot, "x"
	.global _reset

_reset:
	b _startup	/* 0x00 Reset */
	b .		/* 0x04 Undefined instruction */
	b .		/* 0x08 Supervisor call */
	b .		/* 0x0c Prefetch abort */
	b .		/* 0x10 Data abort */
	b .		/* 0x14 Unused */
	b .		/* 0x18 IRQ Interrupt */
	b .		/* 0x1c FIQ Interrupt */

_startup:
	/*
	 * B4.1.130 SCTLR, System Control register
	 *
	 * Vectors Bit
	 * SCTLR.V = 0 Low Exceptions Vector, can remap.
	 * SCTLR.V = 1 High Exceptions Vector, can't remap.
	 */
	mrc p15, 0, r0, c1, c0, 0	@ Read SCTLR into R0
	bic r0, #(1 << 13)		@ Bit clear V
	mcr p15, 0, r0, c1, c0, 0	@ Write SCTLR

	/*
	 * B4.1.156 VBAR, Vector Base Address Register
	 *
	 * Vector Base Address at 31:5
	 * UNK/SBZP 4:0
	*/
	ldr r0, =_reset
	mcr p15, 0, r0, c12, c0, 0

	/* Set stack pointer */
	ldr sp, =stack_top
	bl kern_boot
