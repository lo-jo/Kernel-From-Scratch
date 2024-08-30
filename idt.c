#include "kernel.h"

struct InterruptDescriptorTable{
   unsigned short offset_1;        // offset bits 0..15
   unsigned short selector;        // the 16 bit selector of the code segment to jump to when invoking the handler. This will be our kernel code segment.
   unsigned char  zero;            // unused, set to 0
   unsigned char  type_attributes; // gate type, Will be set to 110 as we are defining an interrupt gate.
   unsigned short offset_2;        // offset bits 16..31
};

struct InterruptDescriptorTable idt[256];

// map Interrupt Requests
void map_irqs(){
	/* ICW1 - begin initialization */
	out_port(0x20 , 0x11);
	out_port(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	out_port(0x21 , 0x20);
	out_port(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	out_port(0x21 , 0x00);  
	out_port(0xA1 , 0x00);  

	/* ICW4 - environment info */
	out_port(0x21 , 0x01);
	out_port(0xA1 , 0x01);

	/* mask all interrupts */
	// out_port(0x21 , 0xff);
	out_port(0xA1 , 0xff);
}

void map_keyboard_idt(){
	/* populate IDT entry of keyboard's interrupt */
	idt[DATA1].offset_1 = (unsigned long)keyboard_handler & 0xffff; // lower 16 bits of address
	idt[DATA1].selector = 0x08; // kernel segment in protected mode
	idt[DATA1].zero = 0;
	idt[DATA1].type_attributes = 0x8e; /* INTERRUPT_GATE */
	idt[DATA1].offset_2 = ((unsigned long)keyboard_handler & 0xffff0000) >> 16;
}
void init_idt(){
	unsigned long idt_address;
	// unsigned long idt_ptr[2];
	IDTDescriptor idt_ptr;

	memset(&idt, 0, sizeof(struct InterruptDescriptorTable) * 256);
	map_keyboard_idt(); // 1. set up IDT entry for keyboard
	map_irqs();			// 2. init and config PICS

	// 3. set IDT pointer
	/* fill the IDT descriptor */
	idt_address = (unsigned long)&idt;
	// idt_ptr[0] = (sizeof (struct InterruptDescriptorTable) * 256) -1 + ((idt_address & 0xffff) << 16);
	// idt_ptr[1] = idt_address >> 16 ; //The lower 5-bits of the access byte is always set to 01110 in binary. This is 14 in decimal.
	idt_ptr.limit = sizeof(struct InterruptDescriptorTable) * 256 - 1;
	idt_ptr.base = idt_address;

	//4. LOAD IDT
    /* This exists in 'start.asm', and is used to load our IDT */
	load_idt(&idt_ptr);
	out_port(0x21 , 0xFD);
	// // UNMASK IRQ1 (keybard) - 0xFD is 11111101 - enables only IRQ1 (keyboard)
}