#include "kernel.h"

struct InterruptDescriptorTable{
   unsigned short offset_1;        // offset bits 0..15
   unsigned short selector;        // a code segment selector in GDT or LDT
   unsigned char  zero;            // unused, set to 0
   unsigned char  type_attributes; // gate type, dpl, and p fields
   unsigned short offset_2;        // offset bits 16..31
} __attribute__ ((packed));

struct InterruptDescriptorTable idt[256];

struct idt_ptr {
  unsigned short  limit;
  unsigned int    base;
} __attribute__ ((packed));

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

	/* mask interrupts */
	out_port(0x21 , 0xff);
	out_port(0xA1 , 0xff);
}

// void map_keyboard_idt(){
// 	/* populate IDT entry of keyboard's interrupt */
// 	idt[DATA1].offset_1 = (unsigned long)keyboard_handler & 0xffff; // lower 16 bits of address
// 	idt[DATA1].selector = 0x08; // kernel segment in protected mode
// 	idt[DATA1].zero = 0;
// 	idt[DATA1].type_attributes = 0x8e; /* INTERRUPT_GATE */
// 	idt[DATA1].offset_2 = ((unsigned long)keyboard_handler & 0xffff0000) >> 16;
// }
// void init_idt(){
// 	unsigned long idt_address;
// 	unsigned long idt_ptr[2];
//
// 	map_keyboard_idt();
// 	map_irqs();
//
// 	/* fill the IDT descriptor */
// 	idt_address = (unsigned long)idt;
// 	idt_ptr[0] = (sizeof (struct InterruptDescriptorTable) * 256) + ((idt_address & 0xffff) << 16);
// 	idt_ptr[1] = idt_address >> 16 ; //The lower 5-bits of the access byte is always set to 01110 in binary. This is 14 in decimal.
//     /* This exists in 'start.asm', and is used to load our IDT */
// 	load_idt(idt_ptr);
// }

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
	unsigned long idt_ptr[2];

	map_keyboard_idt();
	map_irqs();

	/* fill the IDT descriptor */
	idt_address = (unsigned long)idt;
	idt_ptr[0] = (sizeof (struct InterruptDescriptorTable) * 256) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ; //The lower 5-bits of the access byte is always set to 01110 in binary. This is 14 in decimal.
    /* This exists in 'start.asm', and is used to load our IDT */
	load_idt(idt_ptr);
}
