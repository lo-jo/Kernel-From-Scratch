NASM=nasm
GCC=gcc
LD=ld
QEMU=qemu-system-i386

# Compilation flags
NASMFLAGS=-f elf32 -g -F dwarf
GCCFLAGS=-m32 -c -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs -g3
LDFLAGS=-m elf_i386 -T linker.ld

ASM_SOURCE=boot.asm
C_SOURCES=kernel.c idt.c screen.c
ASM_OBJECT=boot.o
C_OBJECTS=$(C_SOURCES:.c=.o)
KERNEL=kernel-100
ISO_PATH=scripts/kernhell.iso

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
	cp ./$(KERNEL) ./scripts

clean:
	rm -f $(ASM_OBJECT) $(C_OBJECTS) $(KERNEL)

emulate: 
	$(QEMU) -kernel $(KERNEL)

boot:
	$(QEMU) -cdrom $(ISO_PATH)

debug-emulate:
	$(QEMU) -s -S -kernel $(KERNEL)

debug-boot:
	$(QEMU) -s -S -d int -cdrom $(ISO_PATH)

.PHONY: all clean fclean emulate
