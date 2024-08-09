#include "kernel.h"
#include "keyboard_map.h"

unsigned int pos = 0;

// https://wiki.osdev.org/Printing_To_Screen
void print_k(int colour, const char *string){
    volatile char *video = (volatile char*)VIDEO;
    while( *string != 0 )
    {
        video[pos++] = *string++;
        video[pos++] = colour;
    }
}



void keyboard_handler_main(void) {
	unsigned char scancode;
	volatile char *video = (volatile char*)VIDEO;
	char keycode;

	/* write EOI */
	write_port(0x20, 0x20);

	/* Read from the keyboard's data buffer */
	scancode = read_port(KEY_STATUS);
	/* Lowest bit of status will be set if buffer is not empty */
	if (scancode & 0x01) {
		keycode = read_port(KEY_PRESSED);
		if(keycode < 0)
			return;
		video[pos++] = keyboard_map[keycode];
		video[pos++] = GREEN;	
	}
}


void clear_screen(int colour){
	volatile char *video = (volatile char*)VIDEO;
	unsigned int j = 0;

	// there are 25 lines each of 80 columns; each element takes 2 bytes
	while(j < 80 * 25 * 2) {
		video[j] = ' ';
		video[j+1] = colour; 		
		j += 2;
	}
}
void kmain(void)
{
	clear_screen(WHITE);
    print_k(PINK, "42");
	map_idt();
	write_port(0x21 , 0xFD);
	while(1);
	return;
}