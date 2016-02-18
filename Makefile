# Makefile for minios-armv7
TOOLCHAIN?= arm-none-eabi-

CC=${TOOLCHAIN}gcc
LD=${TOOLCHAIN}ld
AS=${TOOLCHAIN}as
OBJCOPY=${TOOLCHAIN}objcopy

#
# RPi2 has an ARMv7-A Cortex-A7 processor with VFPv4 Floating-point.
#
# Debug symbols with no optimisations for predictable ASM code generation.
#
CFLAGS+= -mcpu=cortex-a7
CFLAGS+= -g -O0

# Standalone, no libs no start objects.
CFLAGS+= -I.
CFLAGS+= -nodefaultlibs
CFLAGS+= -nostartfiles
CFLAGS+= -nostdlib

# Object files
OBJFILES+= boot.o
OBJFILES+= startup.o
OBJFILES+= subr_prf.o

boot.bin: boot.elf
	$(OBJCOPY) -O binary boot.elf boot.bin

boot.elf: clean subr_prf.o boot.o startup.o
	$(CC) -c subr_prf.c $(CFLAGS)
	$(CC) -c boot.c $(CFLAGS) boot.c
	$(AS) startup.S -o startup.o
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
	qemu-system-arm -singlestep -D /tmp/t.log -d cpu,in_asm -serial stdio\
                -M raspi2 -m 256 -kernel \
                boot.elf -display none

gdb: boot.bin
	qemu-system-arm -S -s -singlestep -serial stdio\
                -M virt -cpu cortex-a15 -m 256 -kernel \
                boot.elf -display none
