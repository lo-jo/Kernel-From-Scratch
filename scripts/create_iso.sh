mkdir -p isodir/boot/grub
cp kernel isodir/boot/
cp grub.cfg isodir/boot/grub/
grub-mkrescue -o kernhell.iso isodir