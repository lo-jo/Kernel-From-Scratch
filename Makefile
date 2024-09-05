NASM=nasm
GCC=gcc
LD=ld
QEMU=qemu-system-i386

# Compilation flags
NASMFLAGS=-f elf32 -g -F dwarf
GCCFLAGS=-m32 -c -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs -g3
LDFLAGS=-m elf_i386 -T linker.ld

ASM_SOURCE=boot.asm
C_SOURCES=kernel.c idt.c screen.c init_data.c print_utils.c
ASM_OBJECT=boot.o
C_OBJECTS=$(C_SOURCES:.c=.o)
KERNEL=kernel-100
ISO_PATH=scripts/kernhell.iso

LOG_FILES_DIRECTORY=./qemudebuglogs
QEMU_LOG_FILE=$(shell date +'%Y%m%d_%H%M%S')_qemu_debug.log

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
	docker compose -f docker-compose.yml up -d --build

clean:
	rm -f $(ASM_OBJECT) $(C_OBJECTS) $(KERNEL)

fclean: clean
	rm -f ./scripts/$(KERNEL)
	rm -rf ./scripts/isodir/ 
	rm -f ./scripts/kernhell.iso
	docker stop $(docker ps -qa) 
	docker rm -f $(docker ps -qa) 
	sudo rm -rf ./scripts/isodir/ 
	sudo rm -f ./scripts/kernhell.iso

re: fclean all

emulate: 
	$(QEMU) -kernel $(KERNEL)

boot:
	$(QEMU) -cdrom $(ISO_PATH)

log-emulate:
	$(QEMU) -d int -D $(LOG_FILES_DIRECTORY)/$(QEMU_LOG_FILE) -kernel $(ISO_PATH)

log-boot:
	$(QEMU) -d int -D $(LOG_FILES_DIRECTORY)/$(QEMU_LOG_FILE) -no-reboot -cdrom $(ISO_PATH)

debug-emulate:
	$(QEMU) -s -S -d int -kernel $(KERNEL)

debug-boot:
	$(QEMU) -s -S -d int -D $(LOG_FILES_DIRECTORY)/$(QEMU_LOG_FILE) -no-reboot -cdrom $(ISO_PATH)

.PHONY: all clean fclean re emulate boot log-emulate log-boot debug-emulate debug-boot
