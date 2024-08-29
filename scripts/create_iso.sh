mkdir -p isodir/boot/grub
cp kernel isodir/boot/kernel
cp grub.cfg isodir/boot/grub/grub.cfg
# Create a GRUB recuperation image
grub-mkrescue /usr/lib/grub/i386-pc -o kernhell.iso isodir