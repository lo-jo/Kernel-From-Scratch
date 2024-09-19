OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS {
	. = 2M; /* Tells GRUB to load the kernel starting at the 2MB mark */
	.multiboot :{ *(.multiboot) }
	.text :{ *(.text) }
	.data :{ *(.data) }
	.bss :{ *(.bss) }
} 
