
arm-none-eabi-gcc -mcpu=cortex-m0plus startup.c -c

arm-none-eabi-gcc -T kl46z256vxx4.ld -nostdlib startup.o -o firmware.elf
