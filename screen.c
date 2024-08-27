#include "kernel.h"

unsigned int pos_x = 0;
unsigned int pos_y = 0;

int get_index(){
	unsigned short index;

	/* equation for finding the index in a linear chunk of memory:
    *  Index = [(y * width) + x] */
	index = pos_y * 80 + pos_x;

	return index;
}

void scroll(void)
{
    unsigned temp;

    if(pos_y >= 25)
    {
        /* select chunk of memory from screen */
        temp = pos_y - 25 + 1;
        /* copy it into screen */
        memcpy((unsigned char *)VIDEO, (unsigned char *)VIDEO + temp * 80 * 2, (25 - temp) * 80 * 2);

        /* set last line to blank */
        // memset ((unsigned short *)VIDEO + (25 - temp) * 80, blank, 80 * 2);
        unsigned char* buffer = (unsigned char *)VIDEO + (25 - temp) * 80 * 2;
        for (int i = 0; i < 80 *2; i+=2){
            buffer[i] = ' ';
            buffer[i+1] = WHITE;
        }
        pos_y = 25 - 1;
    }
}

void update_cursor(void)
{
    unsigned idx;
    idx = get_index();

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'.*/
    out_port(0x3D4, 14);
    out_port(0x3D5, idx >> 8);
    out_port(0x3D4, 15);
    out_port(0x3D5, idx);
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
    scroll();
	update_cursor();
}

// https://wiki.osdev.org/Printing_To_Screen
void print_k(int colour, const char *string){
    volatile char *video = (volatile char*)VIDEO;

    while(*string != 0 ){
        putkey(colour, *string++);
    }
	// update_cursor();
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