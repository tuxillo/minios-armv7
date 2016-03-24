# Makefile for minios-armv7
TOOLCHAIN?= arm-none-eabi-

REVISION=$(shell ./rev.sh)

CC=${TOOLCHAIN}gcc
LD=${TOOLCHAIN}ld
AS=${TOOLCHAIN}as
OBJCOPY=${TOOLCHAIN}objcopy

#
# RPi2 has an ARMv7-A Cortex-A7 processor with VFPv4 Floating-point.
#
# Debug symbols with no optimisations for predictable ASM code generation.
# Force generating code in ARM state
#
CFLAGS+= -mcpu=cortex-a7
CFLAGS+= -marm
CFLAGS+= -g -O0
CFLAGS+= -DMINIOS_VERSION=\"$(REVISION)\"

# Standalone, no libs no start objects.
CFLAGS+= -I.
CFLAGS+= -nodefaultlibs
CFLAGS+= -nostartfiles
CFLAGS+= -nostdlib

# Object files
OBJFILES+= boot.o
OBJFILES+= startup.o
OBJFILES+= exception.o
OBJFILES+= subr_prf.o
OBJFILES+= user.o
OBJFILES+= thread.o
OBJFILES+= syscalls.o
OBJFILES+= uart_pl011.o
OBJFILES+= bcm2836.o
OBJFILES+= core_intr.o

boot.bin: boot.elf
	$(OBJCOPY) -O binary boot.elf boot.bin

boot.elf: clean subr_prf.o boot.o startup.o user.o
	$(CC) -c subr_prf.c $(CFLAGS)
	$(CC) -c user.c $(CFLAGS)
	$(CC) -c boot.c $(CFLAGS)
	$(CC) -c thread.c $(CFLAGS)
	$(CC) -c syscalls.c $(CFLAGS)
	$(CC) -c uart_pl011.c $(CFLAGS)
	$(CC) -c bcm2836.c $(CFLAGS)
	$(CC) -c core_intr.c $(CFLAGS)
	$(AS) startup.S -o startup.o
	$(AS) exception.S -o exception.o
	$(LD) -T boot.ld -nodefaultlibs -nostdlib \
			${OBJFILES} -o boot.elf
uboot: boot.elf
	-cat boot.ld | sed 's/0x8000/0x1000000/g' > boot.u.ld
	$(LD) -T boot.u.ld ${OBJFILES} -o boot.elf
	-rm boot.u.ld
	$(OBJCOPY) -O binary boot.elf boot.bin
	mkimage -A arm -O linux -T kernel -C none -a \
		0x1000000 -e 0x1000000 -n rpi2 -d boot.bin kernel.img

clean:
	-rm -f boot.elf boot.bin kernel.img *.o

run: boot.bin
	qemu-system-arm -singlestep -D /tmp/t.log -d cpu,in_asm,guest_errors,unimp -serial stdio\
                -M raspi2 -m 256 -kernel \
                boot.elf -display none

gdb: boot.bin
	qemu-system-arm -S -s -singlestep -serial stdio\
                -M raspi2 -m 256 -kernel \
                boot.elf -display none
