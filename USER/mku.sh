arm-none-eabi-as -mcpu=arm926ej-s us.s -o us.o
arm-none-eabi-gcc -c -mcpu=arm926ej-s -o $1.o $1.c
arm-none-eabi-ld -T u.ld us.o $1.o -Ttext=0x80000000 -o $1.elf

arm-none-eabi-objcopy -O binary $1.elf $1
sudo mount -o loop sdimage /mnt
sudo cp -av $1 /mnt/bin
sudo umount /mnt


rm *.elf
mv $1.o ../





 



