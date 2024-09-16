NASM=nasm
GCC=gcc
LD=ld
QEMU=qemu-system-i386

# Compilation flags
NASMFLAGS=-f elf32 -g -F dwarf
GCCFLAGS=-m32 -c -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs -g3
LDFLAGS=-m elf_i386 -T linker.ld

# Directories
OBJ_DIR=obj
LOG_FILES_DIRECTORY=./qemudebuglogs
ISO_PATH=scripts/kernhell.iso

# Sources and Objects
ASM_SOURCE=boot.asm
C_SOURCES=kernel.c screen.c print_utils.c gdt.c
ASM_OBJECT=$(OBJ_DIR)/boot.o
C_OBJECTS=$(addprefix $(OBJ_DIR)/, $(C_SOURCES:.c=.o))
KERNEL=kernel-100

QEMU_LOG_FILE=$(shell date +'%Y%m%d_%H%M%S')_qemu_debug.log

all: $(KERNEL)

# Ensure object directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Ensure object directory exists
$(LOG_FILES_DIRECTORY):
	mkdir -p $(LOG_FILES_DIRECTORY)

# Assemble the ASM file into the object directory
$(ASM_OBJECT): $(ASM_SOURCE) $(OBJ_DIR)
	$(NASM) $(NASMFLAGS) $(ASM_SOURCE) -o $(ASM_OBJECT)

# Compile each C source file into the object directory
$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	$(GCC) $(GCCFLAGS) $< -o $@

# Link the object files
$(KERNEL): $(ASM_OBJECT) $(C_OBJECTS) $(LOG_FILES_DIRECTORY)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(ASM_OBJECT) $(C_OBJECTS)
	cp ./$(KERNEL) ./scripts
	docker compose -f docker-compose.yml up -d --build

clean:
	rm -f $(ASM_OBJECT) $(C_OBJECTS) $(KERNEL)
	rm -rf $(OBJ_DIR)
	docker compose -f docker-compose.yml down

fclean: clean
	rm -f ./scripts/$(KERNEL)
	rm -rf ./scripts/isodir/ 
	rm -f ./scripts/kernhell.iso

re: fclean all

emulate: 
	$(QEMU) -kernel $(KERNEL)

boot:
	$(QEMU) -cdrom $(ISO_PATH)

log-emulate:
	$(QEMU) -d int -D $(LOG_FILES_DIRECTORY)/$(QEMU_LOG_FILE) -kernel $(KERNEL)

log-boot:
	$(QEMU) -d int -D $(LOG_FILES_DIRECTORY)/$(QEMU_LOG_FILE) -no-reboot -cdrom $(KERNEL)

debug-emulate:
	$(QEMU) -s -S -d int -kernel $(KERNEL)

debug-boot:
	$(QEMU) -s -S -d int -D $(LOG_FILES_DIRECTORY)/$(QEMU_LOG_FILE) -no-reboot -cdrom $(ISO_PATH)

.PHONY: all clean fclean re emulate boot log-emulate log-boot debug-emulate debug-boot
