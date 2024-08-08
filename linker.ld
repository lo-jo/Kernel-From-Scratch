OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
  . = 1M; /* Tells GRUB to load the kernel starting at the 1MB mark */
  .text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
  .rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}