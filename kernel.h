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

#define SHELL_LINE 24

/******** INTERRUPTS ********/
extern unsigned char keyboard_map[128];

// (asm functions) //
extern void keyboard_handler(void);
extern char in_port(unsigned short port);
extern void out_port(unsigned short port, unsigned char data);
extern void trace_stack(unsigned long *esp, unsigned long *ebp);

/******** GDT ********/
extern void gdt_flush(unsigned int gdt);
void        init_gdt(void);

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
#define SCREEN_NB 9

void clear_screen(char *screen);
void print_k(int colour, const char *string, char *screen, unsigned int screen_nb);
void putkey(int colour, char c, char *screen, unsigned int screen_nb);
void update_cursor(void);
void scroll(void);
void switch_screen(unsigned int screen_nb);
int  get_index(unsigned int screen_nb);
void  init_data(void);
void print_hex(unsigned int value, int color);
void print_stack(void);

/******** IDT ********/
void init_idt(void);

/******** stdlib dupes ********/
void* memset(void* bufptr, int value, int size);
unsigned char* memcpy(unsigned char *dstptr, const unsigned char *srcptr, int size);

/******** screen variables ********/

struct s_screens{
  unsigned char screen[HEIGHT * WIDTH * 2];
};

struct s_index{
  unsigned int pos_x;
  unsigned int pos_y;
};

extern struct s_index indexes[SCREEN_NB];
extern struct s_screens screens[SCREEN_NB];

extern unsigned int active_screen; 

extern unsigned int pos_x;
extern unsigned int pos_y;

#endif
