bits 32

section .multiboot
align 4
    dd 0x1BADB002            ; Magic number
    dd 0x00                  ; Flag for protected mode
    dd -(0x1BADB002 + 0x00)  ; Checksum (magic + flags + checksum = 0)

section .data



section .text
global start
global in_port
global out_port
global gdt_flush
global trace_stack
global trace_stack_test
global halt
global send_triple_fault
global send_reboot

extern kmain 	        ; kmain is defined in the C file
extern gp               ; gdt ptr defined in gdt.c

in_port:
	mov edx, [esp + 4]	; argument  (port nbr) pushed to the edx register
	in al, dx			; Lit un octet dans un port d'entrée/sortie à l'adresse spécifié par le registre DX et met le résultat dans le registre AL.
	ret

out_port:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret

gdt_flush:
    lgdt [gp]
    mov ax, 0x10        ; segment selector
    mov ds, ax          ; data segment register
    mov es, ax          ; extra segment register
    mov fs, ax          ; additional segment
    mov ss, ax
    mov ax, 0x18
	mov gs, ax
    jmp 0x08:flush2

flush2:
    ret

trace_stack:
    mov eax, [esp + 4]    ; Get the address of the esp variable from the stack
    mov ebx, [esp + 8]    ; Get the address of the ebp variable from the stack
    mov [eax], esp        ; Store the current esp into the memory location pointed by eax
    mov [ebx], ebp        ; Store the current ebp into the memory location pointed by ebx
    ret

trace_stack_test:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]
    mov [eax], ebp
    pop ebp
    ret

send_triple_fault:
    int 0x80

send_reboot:
    int 0x81

halt:
    hlt

start:
    mov esp, stack_top       ; Set stack pointer to the top of the stack
    push ebx                 ; Multiboot boot info is in ebx
    call kmain               ; Call kernel main function

section .bss
resb 8192
stack_space:
    resb 8092                ; Reserve 4 KB stack space
stack_top:
