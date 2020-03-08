arm-none-eabi-as -mcpu=arm926ej-s us.s -o us.o
arm-none-eabi-gcc -c -mcpu=arm926ej-s -o $1.o $1.c
arm-none-eabi-ld -T u.ld us.o $1.o -Ttext=0x80000000 -o $1.elf
arm-none-eabi-objcopy -O binary $1.elf $1

echo mounting
echo mounting
echo mounting
echo mounting
sudo mount sdimage /mnt
sudo cp $1 /mnt/bin
sudo ls -l /mnt/bin
sudo umount /mnt
echo unmounting
echo unmounting
echo unmounting
echo unmounting

rm $1
rm *.o *.elf


