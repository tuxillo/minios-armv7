.section .text.boot, "x"
.global _startup

_startup:
	ldr sp, =stack_top
	bl kern_boot
