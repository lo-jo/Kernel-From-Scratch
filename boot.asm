bits 32

section .multiboot
align 4
    dd 0x1BADB002            ; Magic number
    dd 0x00                  ; Flags
    dd -(0x1BADB002 + 0x00)  ; Checksum (magic + flags + checksum = 0)

section .text
global start
extern kmain 	        ; kmain is defined in the C file

start:
    cli 			        ; Block interrupts
    mov esp, stack_top       ; Set stack pointer to the top of the stack
    push ebx                 ; Multiboot boot info is in ebx
    call kmain               ; Call kernel main function
    hlt		 		        ; Halt the CPU

section .bss
align 4
stack_space:
    resb 4096                ; Reserve 4 KB stack space
stack_top:
