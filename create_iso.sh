mkdir -p isodir/boot/grub
cp kernel.bin iso/boot/kernel.bin
echo 'set timeout=0
set default=0
menuentry "My OS" {
    multiboot /boot/kernel.bin
}' > isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir