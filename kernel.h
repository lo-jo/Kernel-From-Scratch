#ifndef KERNEL_H
#define KERNEL_H

/********* COLORS ********/
#define BLACK 0x00
#define BLUE 0x01
#define GREEN 0x02
#define PINK 0x05
#define YELLOW 0x0E
#define WHITE 0x0f
#define VIDEO 0xB8000

/******** INTERRUPTS ********/
extern unsigned char keyboard_map[128];
extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);

#define KEY_PRESSED 0x60
#define KEY_STATUS 0x64

// PIC1 uses port 0x20 for Command and 0x21 for Data
#define CMD1 0x20
#define DATA1 0x21

// PIC2 uses port 0xA0 for Command and 0xA1 for Data.
#define CMD2 0xA0
#define DATA2 0xA1

void map_idt(void);


#endif
