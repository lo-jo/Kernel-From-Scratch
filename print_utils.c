#include "kernel.h"

void print_stack(void) {
    unsigned long esp = 0;
    unsigned long ebp = 0;
    unsigned long *ptr;
	print_k(YELLOW, "Printing stack\n", (char *)VIDEO, active_screen);
    // Call trace_stack to properly initialize esp and ebp
    trace_stack(&esp, &ebp);

    print_k(GREEN, "ESP:\n", (char *)VIDEO, active_screen);
    print_hex(esp, YELLOW);
    print_k(YELLOW, "\nEBP:\n", (char *)VIDEO, active_screen);
    print_hex(ebp, WHITE);

    // Iterate over the stack between ESP and EBP
    for (ptr = (unsigned long *)esp; ptr < (unsigned long *)ebp; ptr++) {
        print_hex(*ptr, WHITE);
        print_k(PINK, "Stack value\n", (char *)VIDEO, active_screen);

        // Safety check to prevent infinite loops due to bad pointers
        if ((unsigned long)ptr > ebp) {
            print_k(PINK, "Warning: Stack pointer out of bounds\n", (char *)VIDEO, active_screen);
            break;
        }
    }
}

void print_stack_test(void) {

  unsigned long *ebp;
  unsigned long eip;
  int frame = 0;

  trace_stack_test(ebp);
  while (ebp && ebp[0] && frame < 10)
  {
    print_k(WHITE, "Stack frame n ", (char *)VIDEO, active_screen);
    putkey(WHITE, frame + 48, (char *)VIDEO, active_screen);
    print_k(WHITE, ":   ", (char *)VIDEO, active_screen);
    putkey(WHITE, '\n', (char *)VIDEO, active_screen);
    print_k(WHITE, "ebp =", (char *)VIDEO, active_screen);
    print_hex((unsigned int)ebp, YELLOW);
    putkey(WHITE, '\n', (char *)VIDEO, active_screen);
    print_k(WHITE, "eip =", (char *)VIDEO, active_screen);
    print_hex(ebp[1], YELLOW);
    putkey(WHITE, '\n', (char *)VIDEO, active_screen);
    ebp = (unsigned long *)ebp[0];
    frame++;
  }
  print_k(WHITE, "End of stack \n", (char *)VIDEO, active_screen);
  return ;
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

    while(*string != 0 ){
        putkey(colour, *string++, screen, screen_nb);
    }
}

void clear_screen(char *screen){
	unsigned int j = 0;

	// there are 25 lines each of 80 columns; each element takes 2 bytes
	while(j < 80 * 25 * 2) {
		screen[j] = ' ';
		screen[j+1] = WHITE; 		
		j += 2;
	}
}
