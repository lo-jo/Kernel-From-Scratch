#ifndef KERNEL_H
#define KERNEL_H

typedef struct {
    unsigned short limit;  // Size of the IDT in bytes (limit)
    unsigned long base;   // Base address of the IDT
} IDTDescriptor;

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
// (asm functions) //
extern void keyboard_handler(void);
extern char in_port(unsigned short port);
extern void out_port(unsigned short port, unsigned char data);
extern void load_idt(IDTDescriptor *idt_ptr);
// extern void load_idt(unsigned long idt_ptr[2]);

/******** Keyboard routines ********/
#define KEY_PRESSED 0x60
#define KEY_STATUS 0x64

// PIC1 uses port 0x20 for Command and 0x21 for Data
#define CMD1 0x20
#define DATA1 0x21

// PIC2 uses port 0xA0 for Command and 0xA1 for Data.
#define CMD2 0xA0
#define DATA2 0xA1


/******** SCREEN ********/
#define HEIGHT 25
#define WIDTH 80

void clear_screen(void);
void print_k(int colour, const char *string);
void putkey(int colour, char c);
void update_cursor(void);
void scroll(void);
int  get_index(void);

/******** IDT ********/
void init_idt(void);

/******** stdlib dupes ********/
unsigned char* memcpy(unsigned char *dstptr, const unsigned char *srcptr, int size);
void* memset(void* bufptr, int value, int size);

#endif
