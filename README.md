# Kernel-From-Scratch

A minimal Kernel from scratch bootable with GRUB, written in ASM and C.

This project wa done in collaboration with [@Alban](https://github.com/albibou).

## Features
- Printing to screen
- Scroll and cursor support
- Color support
- Keyboard entries
- Different screens and keyboard shortcuts to switch  between them
- Global Table Descriptor
- Basic shell commands (halt, reboot, clear...)
- Stack tracing function
- Helper functions (printk, ...)

## Constraints
- Must compile without dependencies
- i386 architecture
- Source code has to be no more than 10MB

# General info
### Booting with GRUB
When you turn on a computer, it loads the BIOS from flash memory, which runs hardware self-tests and initializes components. The BIOS then looks for bootable devices and transfers control to the bootloader on the chosen device. The bootloader's job is to locate the kernel image and load it into memory, while also switching the CPU from real mode (a limited 16-bit mode for backward compatibility) to protected mode (a 32-bit mode with better control over resources).

GRUB, the "Grand Unified Bootloader," is commonly used in GNU/Linux systems. It follows the Multiboot specification, which defines how a kernel should be loaded into memory.

##### Multiboot
By including a Multiboot header at the start of our kernel, we can let GRUB handle the loading process. An added benefit of using GRUB is that it takes care of switching the CPU from real mode to protected mode.

Thanks to the Multiboot Standard, which describes an easy interface between the bootloader and the operating system kernel, it is possible to put a few magic values in some global variables (known as a multiboot header), which is searched for by the bootloader. When it sees these values, it recognizes the kernel as multiboot compatible.

### Screen
We'll be using the screen as a memory mapped device.
Specific positions in memory correspond to certain positions on the screen.
``` 0xb8000 ``` is the upper-left corner position on the screen.

### Reading from and writing to I/O ports
I/O ports are accessed using the x86 instructions ```in``` and ```out```

- [In](https://www.gladir.com/LEXIQUE/ASM/in.htm) 
(``` in src, dest ```) \
The IN instruction almost always has the operands AX and DX (or EAX and EDX) associated with it. DX (src) frequently holds the port address to read, and AX (dest) receives the data from the port.

- [Out](https://www.gladir.com/LEXIQUE/ASM/out.htm) \
The OUT instruction is very similar to the IN instruction. OUT outputs data from a given register (src) to a given output port (dest).

#### Interrupts
Signal sent to the processor by the hardware indicating an event.

Load Interrupt Descriptor Tables:\
https://www.gladir.com/LEXIQUE/ASM/lidt.htm

Set interrupt flag\
https://www.gladir.com/LEXIQUE/ASM/sti.htm
https://en.wikibooks.org/wiki/X86_Assembly/Other_Instructions


#### Interrupt descriptor Table 
The Interrupt Descriptor Table, or IDT, is used in order to show the processor what Interrupt Service Routine (ISR) to call to handle either an exception or an 'int' opcode (in assembly). IDT entries are also called by Interrupt Requests whenever a device has completed a request and needs to be serviced. 

In an IDT, the base address specified in the descriptor is actually the address of the Interrupt Service Routine (our keyboard handler) that the processor should call when this interrupt is 'raised' (called).

https://wiki.osdev.org/Interrupt_Descriptor_Table
https://pdos.csail.mit.edu/6.828/2018/readings/i386/s09_04.htm
http://www.osdever.net/bkerndev/Docs/idt.htm


### The GDT 
The Global Descriptor Table defines base access and privileges for certain parts of memory.
GRUB installs a GDT but if we overwite the area of memory that GRUB was loaded to, the GDT will be trashed and will cause a triple fault, causing the machine to be reset.

To prevent that problem from happening, the GDT can be set on its own in a place in memory that is known and that we can access to.


https://wiki.osdev.org/Global_Descriptor_Table

1. Building the GDT
2. Telling the processor where it is
3. loading the processor registers with our entries
Registers such as CS, DS, ES, FS... are segments.
The CS register is the code segment that tells the procession which offset in the GDT that will find the acess privilege to execute our code.

### Linker
Our OS can't link the ASM and the C executables together. \
By using [ld](https://www.math.utah.edu/docs/info/ld_toc.html#SEC3), we can write a linker script that will just do that.

### Creating a bootable disk image
https://wiki.osdev.org/Bare_Bones#Building_a_bootable_cdrom_image

### System emulation
Running our kernel is possible with tools such as QEMU.
``` make emulate ``` (without GRUB)

## Resources
"OS Bible": https://wiki.osdev.org/Expanded_Main_Page\
Linker: https://www.math.utah.edu/docs/info/ld_3.html#SEC4\
Tutorials:\
https://ics.uci.edu/~aburtsev/143A/hw/hw4-boot-into-c/hw4-boot-into-c.html
https://wiki.osdev.org/Bare_Bones\
i/o devices : https://pages.cs.wisc.edu/~remzi/OSTEP/file-devices.pdf

ram kernel mode
https://www.cse.iitb.ac.in/~mythili/os/notes/old-notes/notes-kernel-mode.txt
