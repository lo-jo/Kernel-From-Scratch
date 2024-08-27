# Define the tools
NASM=nasm
GCC=gcc
LD=ld
QEMU=qemu-system-i386

# Compilation flags
NASMFLAGS=-f elf32
GCCFLAGS=-m32 -c -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs
LDFLAGS=-m elf_i386 -T linker.ld

# Define the source files and output files
ASM_SOURCE=boot.asm
C_SOURCES=kernel.c idt.c screen.c
ASM_OBJECT=boot.o
C_OBJECTS=$(C_SOURCES:.c=.o)
KERNEL=kernel

# Default target
all: $(KERNEL)

# Assemble the ASM file
$(ASM_OBJECT): $(ASM_SOURCE)
	$(NASM) $(NASMFLAGS) $(ASM_SOURCE) -o $(ASM_OBJECT)

# Compile each C source file into an object file
%.o: %.c
	$(GCC) $(GCCFLAGS) $< -o $@

# Link the object files
$(KERNEL): $(ASM_OBJECT) $(C_OBJECTS)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(ASM_OBJECT) $(C_OBJECTS)

# Clean up the generated files
clean:
	rm -f $(ASM_OBJECT) $(C_OBJECTS) $(KERNEL)

# Emulate the kernel
emulate: $(KERNEL)
	$(QEMU) -kernel $(KERNEL)

# Phony targets
.PHONY: all clean fclean emulate
