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
global load_idt

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

load_idt:
	mov edx, [esp + 4] 	; port
	lidt [edx]			; load interrupt description table
	sti 				; Set Interrupt Flag to 1 (on)
	ret

keyboard_handler:                 
	call    keyboard_routine ; interrupt service routine (ISR)
	iretd

start:
    cli 			         ; Clears the interrupt flag
    mov esp, stack_top       ; Set stack pointer to the top of the stack
    push ebx                 ; Multiboot boot info is in ebx
    call kmain               ; Call kernel main function
    hlt		 		         ; Halt the CPU

section .bss
align 16
stack_space:
    resb 8192                ; Reserve 4 KB stack space
stack_top:
