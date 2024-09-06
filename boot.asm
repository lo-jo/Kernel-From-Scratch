bits 32

section .multiboot
align 4
    dd 0x1BADB002            ; Magic number
    dd 0x00                  ; Flag for protected mode
    dd -(0x1BADB002 + 0x00)  ; Checksum (magic + flags + checksum = 0)

section .text
global start
global keyboard_handler
global in_port
global out_port

extern kmain 	        ; kmain is defined in the C file
extern keyboard_routine

in_port:
	mov edx, [esp + 4]	; argument  (port nbr) pushed to the edx register
	in al, dx			; Lit un octet dans un port d'entrée/sortie à l'adresse spécifié par le registre DX et met le résultat dans le registre AL.
	ret

out_port:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret

start:
    mov esp, stack_top       ; Set stack pointer to the top of the stack
    cli 			         ; Clears the interrupt flag
    mov esp, stack_top       ; Set stack pointer to the top of the stack
    push ebx                 ; Multiboot boot info is in ebx
    call kmain               ; Call kernel main function

section .bss
align 16
stack_space:
    resb 4096                ; Reserve 4 KB stack space
stack_top:
