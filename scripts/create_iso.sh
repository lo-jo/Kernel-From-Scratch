mkdir -p isodir/boot/grub
cp kernel-100 isodir/boot/
cp grub.cfg isodir/boot/grub/
grub-mkrescue -o kernhell.iso isodir
