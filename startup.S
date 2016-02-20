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
