# Kernel-From-Scratch #1

A minimal Kernel from scratch bootable with GRUB, written in ASM and C.

## Features
- Printing to screen
- Helper functions : ****
- Scroll and cursor support
- Color support
- Keyboard entries
- Different screens and keyboard shortcuts to switch  between them 

## Constraints
- Must compile without dependencies
- i386 architecture
- Source code has to be no more than 10MB

# Basic info
### Booting with GRUB
When you turn on a computer, it loads the BIOS from flash memory, which runs hardware self-tests and initializes components. The BIOS then looks for bootable devices and transfers control to the bootloader on the chosen device. The bootloader's job is to locate the kernel image and load it into memory, while also switching the CPU from real mode (a limited 16-bit mode for backward compatibility) to protected mode (a 32-bit mode with better control over resources). Default way is to load the first sector (512 bytes)
from disk into the memory location at 0x7c00.

GRUB, the "Grand Unified Bootloader," is commonly used in GNU/Linux systems. It follows the Multiboot specification, which defines how a kernel should be loaded into memory. By including a Multiboot header at the start of our kernel, we can let GRUB handle the loading process. An added benefit of using GRUB is that it takes care of switching the CPU from real mode to protected mode.

### Screen
We'll be using the screen as a memory mapped device.
Specific positions in memory correcpond to certain positions on the screen.
``` 0xb8000 ``` is the upper-left corner position on the screen.

### Linker
Our OS can't link the ASM and the C executables together. \
By using [ld](https://www.math.utah.edu/docs/info/ld_toc.html#SEC3), we can write a linker script that will just do that.

### Creating a disk image
NOW THAT IS ONE THING THAT I CANT GET TO DO

### System emulation
Running our kernel is possible with tools such as QEMU.
``` make emulate ``` (without GRUB)

## Resources
https://wiki.osdev.org/Expanded_Main_Page
Linker : https://www.math.utah.edu/docs/info/ld_3.html#SEC4
https://ics.uci.edu/~aburtsev/143A/hw/hw4-boot-into-c/hw4-boot-into-c.html
i/o devices : https://pages.cs.wisc.edu/~remzi/OSTEP/file-devices.pdf