arm-none-eabi-as -mcpu=arm926ej-s us.s -o us.o

arm-none-eabi-gcc -c -mcpu=arm926ej-s -o $1.o $1.c #2> /dev/null

arm-none-eabi-ld -T u.ld us.o $1.o mtxlib -Ttext=0x80000000 -o $1.elf
arm-none-eabi-objcopy -O binary $1.elf $1

sudo mount sdimage /mnt
sudo cp -av $1 /mnt/bin
#ls -l /mnt/bin
sudo umount /mnt

rm $1
rm *.o



 



