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
	.global _gouser

_reset:
	b _startup	/* 0x00 Reset */
	b _e_undef	/* 0x04 Undefined instruction */
	b _e_svc	/* 0x08 Supervisor call */
	b _e_pref_abort	/* 0x0c Prefetch abort */
	b _e_data_abort	/* 0x10 Data abort */
	b .		/* 0x14 Unused */
	b _e_irq	/* 0x18 IRQ Interrupt */
	b _e_fiq	/* 0x1c FIQ Interrupt */

_startup:
	/*
	 * B1.3.3 Program Status Registers (PSRs)
	 *
	 * On reset the SPSRs are in status UNKNOWN.
	 *
	 * B9.3.2 CPS (ARM)
	 * Change Processor State instruction to enable/disable
	 * IRQ or change to a different mode.
	 *
	 */
	cpsid if	@ Disable IRQ/FIQ

	/*
	 * B4.1.130 SCTLR, System Control register
	 *
	 * Vectors Bit
	 * SCTLR.V = 0 Low Exceptions Vector, can remap.
	 * SCTLR.V = 1 High Exceptions Vector, can't remap.
	 */
	mrc p15, 0, r0, c1, c0, 0	@ Read SCTLR into R0
	bic r0, #(1 << 13)		@ Set SCTLR.V to 0
	bic r0, #(1 << 12)		@ Set SCTLR.I to 0
	bic r0, #(1 << 11)		@ Set SCTLR.Z to 0
	bic r0, #(1 << 2)		@ Set SCTLR.C to 0
	mcr p15, 0, r0, c1, c0, 0	@ Write SCTLR

	/*
	 * B4.1.156 VBAR, Vector Base Address Register
	 *
	 * Vector Base Address at 31:5
	 * UNK/SBZP 4:0
	*/
	ldr r0, =_reset
	mcr p15, 0, r0, c12, c0, 0

	/* Set kernel stack pointer */
	ldr sp, =kernstack_top
	ldr r0, =sctlr_text
	mrc p15, 0, r1, c1, c0, 0
	bl kprintf
	bl kern_boot

_gouser:
	/*
	 * B1.3.2 ARM core registers
	 *
	 * Since System mode doesn't have its own registers for
	 * SP, LR it shares them with User mode.
	*/
	stmfd sp!, {r0-r11,ip,lr}

	msr cpsr_c, #0x1f	@ Switch to System mode
	cmp r1, #0		@ Check if stack passed
	bne _load_custom_stack	@ Set another stack if one is passed
	ldr sp, =usrstack_top	@ Set stack for user/sys mode
	bl  _swi

_load_custom_stack:
	mov sp, r1		@ Set a thread stack

_swi:
	msr cpsr_c, #0xd3	@ Switch to svc mode
	mrs r4, cpsr		@ For saving SPSR
	msr spsr, r4		@ Read in CSPR to SPSR for manipulation
	msr spsr_c, #0x10	@ User mode for the exception return
	mov lr, r0		@ Userland function to switch to
	subs pc, lr, #0		@ Exception return
sctlr_text:
	.asciz "sctlr=0x%x\n"
