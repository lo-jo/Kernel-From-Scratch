#include "kernel.h"
#include "keyboard_map.h"

unsigned int pos_x = 0;
unsigned int pos_y = 0;

int get_index(){
	unsigned short index;

	/* equation for finding the index in a linear
    *  chunk of memory:
    *  Index = [(y * width) + x] */
	index = pos_y * 80 + (pos_x);

	return index;
}

void update_cursor(void)
{
    unsigned idx;
    idx = get_index();

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    write_port(0x3D4, 14);
    write_port(0x3D5, idx >> 8);
    write_port(0x3D4, 15);
    write_port(0x3D5, idx);
}

void putkey(int colour, char c){
	unsigned short *index;

	if (c == '\b'){
		if (pos_x != 0){
        	pos_x--;
		}
	}
	else if (c == '\n'){
        pos_x = 0;
        pos_y++;
	}
	else{
		index = (unsigned short *)VIDEO + get_index();
		*index = c | colour << 8;
		pos_x++;
	}
	if(pos_x >= 80)
    {
        pos_x = 0;
        pos_y++;
    }
	update_cursor();
}

// https://wiki.osdev.org/Printing_To_Screen
void print_k(int colour, const char *string){
    volatile char *video = (volatile char*)VIDEO;

    while(*string != 0 ){
        putkey(colour, *string++);
    }
	update_cursor();
}

void keyboard_handler_main(void) {
	unsigned char scancode;
	char keycode;

	/* write EOI */
	write_port(0x20, 0x20);

	/* Read from the keyboard's data buffer */
	scancode = read_port(KEY_STATUS);
	/* Lowest bit of key status will be set if buffer is not empty */
	if (scancode & 0x01){
		keycode = read_port(KEY_PRESSED);
		if(keycode < 0)
			return;
		putkey(GREEN, keyboard_map[keycode]);
	}
}

void clear_screen(){
	volatile char *video = (volatile char*)VIDEO;
	unsigned int j = 0;

	// there are 25 lines each of 80 columns; each element takes 2 bytes
	while(j < 80 * 25 * 2) {
		video[j] = ' ';
		video[j+1] = WHITE; 		
		j += 2;
	}
}
void kmain(void)
{
	// ft_write(1, "hello", 5);
	clear_screen();
    print_k(PINK, "42\n");
	init_idt();
	// init keyboard - 0xFD is 11111101 - enables only IRQ1 (keyboard)
	write_port(0x21 , 0xFD);
	while(1);
	return;
}