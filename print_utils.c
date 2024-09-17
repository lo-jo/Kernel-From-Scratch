#include "kernel.h"

void putshell(int color, char c, char *screen)
{
	unsigned short *index;
	index = (unsigned short *)screen + SHELL_LINE * 80 + indexes[0].pos_x;

	if (c == '\b'){
		if (indexes[active_screen].pos_x != 0){
			if (indexes[active_screen].pos_x != 1){
				indexes[active_screen].pos_x--;
			}
			c = ' ';
			color = WHITE;
			*index = c | color << 8;
		}
	}
	else if (c < 0  && c > -10)
    	switch_screen((unsigned int)(-c - 1));
	else if (c == '\n'){
		// ADD FUNCTION TO PARSE INPUT
		clear_line(screen, SHELL_LINE);
		indexes[active_screen].pos_y++;
		indexes[active_screen].pos_x = 0;
		putshell(WHITE, '>', screen);
	}
	else{
		*index = c | color << 8;
		indexes[active_screen].pos_x++;
	}
	if (indexes[active_screen].pos_x >= WIDTH){
		clear_line(screen, SHELL_LINE);
		indexes[active_screen].pos_x = 0;
		indexes[active_screen].pos_y++;
		putshell(WHITE, '>', screen);
	}
	if (indexes[active_screen].pos_y >= HEIGHT){
		scroll();
	}
	update_cursor();
}

void print_hex(unsigned int value, int color){
	char *hex = "0123456789abcdef";
	char buffer[9];
	int i;

	buffer[8] = 0;
	for(i = 7; i >= 0; i--){
		buffer[i] = hex[value & 0xF];
		value >>= 4;
	}
	print_k(color, buffer, (char *)VIDEO, active_screen);
}

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


