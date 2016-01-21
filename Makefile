# Makefile for minios-armv7
TOOLCHAIN?= arm-none-eabi-

CC=${TOOLCHAIN}gcc

CFLAGS+= -g -O0
CFLAGS+= -nodefaultlibs
CFLAGS+= -nostartfiles
CFLAGS+= -nostdlib
#CFLAGS+= -Wall
CFLAGS+= -mcpu=cortex-a15
boot.elf: subr_prf.o boot.o
	$(TOOLCHAIN)gcc -c subr_prf.c $(CFLAGS)
	$(TOOLCHAIN)gcc -c boot.c $(CFLAGS) boot.c
	$(TOOLCHAIN)gcc subr_prf.o boot.c $(CFLAGS) -o boot.elf

clean:
	-rm -f boot.elf *.o

run: boot.elf
	qemu-system-arm -singlestep -D /tmp/t.log -d cpu,in_asm -serial stdio\
                -M virt -cpu cortex-a15 -m 256 -kernel \
                boot.elf -display none

gdb: boot.elf
	qemu-system-arm -S -s -serial stdio\
                -M virt -cpu cortex-a15 -m 256 -kernel \
                boot.elf -display none
