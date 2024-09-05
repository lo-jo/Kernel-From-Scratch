#include "kernel.h"

void putkey(int colour, char c, char *screen, unsigned int screen_nb){
	unsigned short *index;

	if (c == '\b'){
		if (indexes[screen_nb].pos_x != 0){
        	indexes[screen_nb].pos_x--;
		      index = (unsigned short *)screen + get_index(screen_nb);
          c = ' ';
          colour = WHITE;
		      *index = c | colour << 8;
		}
	}
  else if (c < 0  && c > -10)
    switch_screen((unsigned int)(-c - 1));
	else if (c == '\n'){
        indexes[screen_nb].pos_x = 0;
        indexes[screen_nb].pos_y++;
	}
	else{
		index = (unsigned short *)screen + get_index(screen_nb);
		*index = c | colour << 8;
		indexes[screen_nb].pos_x++;
	}
	if(indexes[screen_nb].pos_x >= 80)
    {
        indexes[screen_nb].pos_x = 0;
        indexes[screen_nb].pos_y++;
    }
    scroll();
	update_cursor();
}

// https://wiki.osdev.org/Printing_To_Screen
void print_k(int colour, const char *string, char *screen, unsigned int screen_nb){
    //volatile char *video = (volatile char*)VIDEO;

    while(*string != 0 ){
        putkey(colour, *string++, screen, screen_nb);
    }
}

void clear_screen(char *screen){
	//volatile char *video = (volatile char*)VIDEO;
	unsigned int j = 0;

	// there are 25 lines each of 80 columns; each element takes 2 bytes
	while(j < 80 * 25 * 2) {
		screen[j] = ' ';
		screen[j+1] = WHITE; 		
		j += 2;
	}
}
