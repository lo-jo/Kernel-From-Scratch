#include "kernel.h"

struct InterruptDescriptor{
   unsigned short offset_1;        // offset bits 0..15
   unsigned short selector;        // a code segment selector in GDT or LDT
   unsigned char  zero;            // unused, set to 0
   unsigned char  type_attributes; // gate type, dpl, and p fields
   unsigned short offset_2;        // offset bits 16..31
};

struct InterruptDescriptor idt[256];

void kb_init(void)
{
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	write_port(0x21 , 0xFD);
}

void map_idt(){
    unsigned long keyboard_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	/* populate IDT entry of keyboard's interrupt */
	keyboard_address = (unsigned long)keyboard_handler; 
	idt[DATA1].offset_1 = keyboard_address & 0xffff; // lower 16 bits of address
	idt[DATA1].selector = 0x08; // kernel segment in protected mode
	idt[DATA1].zero = 0;
	idt[DATA1].type_attributes = 0x8e; /* INTERRUPT_GATE */
	idt[DATA1].offset_2 = (keyboard_address & 0xffff0000) >> 16;

	/* ICW1 - begin initialization */
	write_port(0x20 , 0x11);
	write_port(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	write_port(0x21 , 0x20);
	write_port(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	write_port(0x21 , 0x00);  
	write_port(0xA1 , 0x00);  

	/* ICW4 - environment info */
	write_port(0x21 , 0x01);
	write_port(0xA1 , 0x01);


	/* mask interrupts */
	write_port(0x21 , 0xff);
	write_port(0xA1 , 0xff);

	/* fill the IDT descriptor */
	idt_address = (unsigned long)idt;
	idt_ptr[0] = (sizeof (struct InterruptDescriptor) * 256) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;
//The lower 5-bits of the access byte is always set to 01110 in binary. This is 14 in decimal.
    /* This exists in 'start.asm', and is used to load our IDT */
	load_idt(idt_ptr);
}