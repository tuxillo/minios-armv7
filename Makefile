TOOLCHAIN?= arm-none-eabi-

CFLAGS+= -I/usr/include/newlib
boot.elf: syscalls.c boot.c
	$(TOOLCHAIN)gcc -c syscalls.c $(CFLAGS) -O2 -nostartfiles -mcpu=cortex-a15
	$(TOOLCHAIN)gcc -c boot.c $(CFLAGS) -O2 -nostartfiles -mcpu=cortex-a15 boot.c
	$(TOOLCHAIN)gcc syscalls.o boot.c $(CFLAGS) -O2 -nostartfiles -mcpu=cortex-a15 -o boot.elf

clean:
	-rm -f boot.elf *.o

run: boot.elf
	qemu-system-arm -singlestep -D /tmp/t.log -d cpu,in_asm -serial stdio\
                -M virt -cpu cortex-a15 -m 256 -kernel \
                boot.elf -display none

