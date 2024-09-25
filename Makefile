NASM=nasm
GCC=gcc
LD=ld
QEMU=qemu-system-i386

# Compilation flags
NASMFLAGS=-f elf32 -g -F dwarf
GCCFLAGS=-m32 -c -fno-builtin -fno-stack-protector -fno-omit-frame-pointer -nostdlib -nodefaultlibs -g3
LDFLAGS=-m elf_i386 -T src/linker.ld

# Directories
SRC_DIR=src
LOG_FILES_DIR=./qemudebuglogs
ISO_PATH=scripts/kernhell.iso

# Sources and Objects
ASM_SOURCE=src/boot.asm \

C_SOURCES=src/kernel.c \
					src/screen.c \
					src/print_utils.c \
					src/gdt.c \
					src/shell_utils.c \

ASM_OBJECT=$(ASM_SOURCE:.asm=.o)
C_OBJECTS=$(C_SOURCES:.c=.o)
KERNEL=kernel-100

QEMU_LOG_FILE=$(shell date +'%Y%m%d_%H%M%S')_qemu_debug.log

all: $(KERNEL)

# Ensure logfiles directory exists
$(LOG_FILES_DIR):
	mkdir -p $(LOG_FILES_DIR)

# Assemble the ASM file into the object directory
$(ASM_OBJECT): $(ASM_SOURCE) 
	$(NASM) $(NASMFLAGS) $(ASM_SOURCE) -o $(ASM_OBJECT)

# Compile each C source file into the directory
%.o: %.c
	$(GCC) $(GCCFLAGS) $< -o $@

# Link the object files
$(KERNEL): $(ASM_OBJECT) $(C_OBJECTS) $(LOG_FILES_DIR)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(ASM_OBJECT) $(C_OBJECTS)
	cp ./$(KERNEL) ./scripts
	docker compose -f docker-compose.yml up -d --build

clean:
	rm -f $(ASM_OBJECT) $(C_OBJECTS) $(KERNEL)
	rm -f ./scripts/$(KERNEL)
	rm -rf ./scripts/isodir/ 
	rm -rf $(LOG_FILES_DIR)
	docker compose -f docker-compose.yml down

fclean: clean
	rm -f ./scripts/kernhell.iso
	docker system prune -af

re: fclean all

emulate: 
	$(QEMU) -kernel $(KERNEL)

boot:
	$(QEMU) -cdrom $(ISO_PATH)

log-emulate:
	$(QEMU) -d int -D $(LOG_FILES_DIRECTORY)/$(QEMU_LOG_FILE) -kernel $(ISO_PATH)

log-boot:
	$(QEMU) -d int -D $(LOG_FILES_DIRECTORY)/$(QEMU_LOG_FILE) -no-reboot -cdrom $(KERNEL)

debug-emulate:
	$(QEMU) -s -S -d int -kernel $(KERNEL)

debug-boot:
	$(QEMU) -s -S -no-reboot -cdrom $(ISO_PATH)

.PHONY: all clean fclean re emulate boot log-emulate log-boot debug-emulate debug-boot
