OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS {
	. = 2M; /* Tells GRUB to load the kernel starting at the 2MB mark */
	.multiboot : ALIGN(4K) { *(.multiboot) }
	.text : ALIGN(4K) { *(.text) }
	.data : ALIGN(4K) { *(.data) }
	.bss : ALIGN(4K) { *(.bss) }
} 
