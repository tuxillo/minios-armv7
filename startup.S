.section .text.boot, "x"
.global _reset

_reset:
	b _startup	/* 0x00 Reset */
	b .	/* 0x04 Undefined instruction */
	b .	/* 0x08 Supervisor call */
	b .	/* 0x0c Prefetch abort */
	b .	/* 0x10 Data abort */
	b .	/* 0x14 Unused */
	b .	/* 0x18 IRQ Interrupt */
	b .	/* 0x1c FIQ Interrupt */

_startup:
	/* Low exception vectors */
	mrc p15, 0, r0, c1, c0, 0
	bic r0, #(1 << 13)

	/* Attempt to set VBAR */
	mcr p15, 0, r0, c1, c0, 0
	ldr r0, =_reset

	/* Set stack pointer */
	ldr sp, =stack_top
	bl kern_boot
