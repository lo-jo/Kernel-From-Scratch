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
C_SOURCE=kernel.c
ASM_OBJECT=boot.o
C_OBJECT=kernel.o
KERNEL=kernel.bin

# Default target
all: $(KERNEL)

# Assemble the ASM file
$(ASM_OBJECT): $(ASM_SOURCE)
	$(NASM) $(NASMFLAGS) $(ASM_SOURCE) -o $(ASM_OBJECT)

# Compile the C file
$(C_OBJECT): $(C_SOURCE)
	$(GCC) $(GCCFLAGS) $(C_SOURCE) -o $(C_OBJECT)

# Link the object files
$(KERNEL): $(ASM_OBJECT) $(C_OBJECT)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(ASM_OBJECT) $(C_OBJECT)

# Clean up the generated files
clean:
	rm -f $(ASM_OBJECT) $(C_OBJECT) $(KERNEL)

fclean: clean
	rm -f *~ \#*\# *.bak

emulate: $(KERNEL)
	$(QEMU) -kernel $(KERNEL)

# Phony targets
.PHONY: all clean
