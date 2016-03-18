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

	.global _e_undef
	.global _e_svc
	.global _e_pref_abort
	.global _e_data_abort
	.global _e_irq
	.global _e_fiq

_e_undef:
	bl .

_e_svc:
	msr cpsr_c, #0x1f	@ Switch to system mode
	mov r5, lr		@ Save LR of the user thread
	msr cpsr_c, #0xd3
	bl  syscall_handler
	cmp r0, #1
	beq ret_svc
	mov lr, r5
	subs pc, lr, #0
ret_svc:
	ldmfd sp!, {r0-r11, ip,lr}
	bx lr

_e_pref_abort:
	bl .

_e_data_abort:
	ldr sp, =abtstack_top
	ldr r0, =abt_text
	mov r1, lr
	mrc p15, 0, r2, c6, c0, 0
	mrs r3, cpsr
	bl kprintf
	bl .

_e_irq:
	cpsid i			   @ Disable interrupts

	cmp sp, #0x0		   @ Check if stack is null
	ldreq sp, =irqstack_top	   @ Load stack top at init

	stmfd sp!, {r0-r11}	   @ Save context

	movw r4, #0x60		   @ Load core0 timer source
	movt r4, #0x4000
	ldr r0, [r4, #0]

	msr cpsr_c, #0xd3	   @ Switch to svc mode
	push {ip, lr}
	bl irq_handler		   @ IRQ handler in svc mode
	pop {ip,lr}

	ldmfd sp!, {r0-r11}
	cpsie i
	bx lr

_e_fiq:
	ldr sp, =kernstack_top
	ldr r0, =fiq_text
	mov r1, lr 
	bl kprintf
	bl .

syscall_text:
	.asciz "[svc] Syscall %d used!\n"
undef_text:
	.asciz "[und] Undefined exception %p\n"
irq_text:
	.asciz "[irq] IRQ exception core0=0x%x lr=0x%x cpsr=0x%x\n"
fiq_text:
	.asciz "[fiq] FIQ exception %p\n"
pref_abort:
	.asciz "pref abort %p\n"
abt_text:
	.asciz "[abt] data abort lr=0x%x dfar=0x%x cpsr=0x%x\n"
