#include "kernel.h"
#include "keyboard_map.h"

struct s_index indexes[SCREEN_NB];
struct s_screens screens[SCREEN_NB];

void clear_line(char *screen, unsigned int line)
{
	unsigned short *index;
	index = (unsigned short *)screen + line * 80;
	for (int i = 0; i < 80 * 2; i += 2) {
			screen[line * 80 * 2 + i] = ' ';
			screen[line * 80 * 2 + i + 1] = WHITE;
		}
}

void minishell_that(int color, char c, char *screen)
{
	unsigned short *index;
	index = (unsigned short *)screen + SHELL_LINE * 80 + indexes[0].pos_x;
	// get_index(active_screen);
	if (c == '\b'){
		if (indexes[active_screen].pos_x != 0){
			indexes[active_screen].pos_x--;
			c = ' ';
			color = WHITE;
			*index = c | color << 8;
		}
	}
	else if (c == '\n'){
		// clear_terminal(screen);
		clear_line(screen, SHELL_LINE);
		indexes[active_screen].pos_y++;
		indexes[active_screen].pos_x = 0;
		minishell_that(WHITE, '>', screen);
	}
	else{
		*index = c | color << 8;
		indexes[active_screen].pos_x++;
	}
	if (indexes[active_screen].pos_x >= WIDTH){
		clear_line(screen, SHELL_LINE);
		indexes[active_screen].pos_x = 0;
		indexes[active_screen].pos_y++;
		minishell_that(WHITE, '>', screen);
	}
	if (indexes[active_screen].pos_y >= HEIGHT){
		scroll();
	}
	update_cursor();
}

void* memset(void* bufptr, int value, int size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (int i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}

unsigned char* memcpy(unsigned char *dstptr, const unsigned char *srcptr, int size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (int i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}

void keyboard_routine(void) {
	unsigned char scancode;
	char keycode;

	/* Read from the keyboard's data buffer */
	scancode = in_port(KEY_STATUS);
	/* Lowest bit of key status will be set if buffer is not empty */
	if (scancode & 0x01){
		keycode = in_port(KEY_PRESSED);
		if(keycode < 0)
			return;
		if (active_screen == 0)
			minishell_that(WHITE, keyboard_map[keycode], (char *)VIDEO);
		else
			putkey(GREEN, keyboard_map[keycode], (char *)VIDEO, active_screen);
	}
}

void  init_data(void)
{
  for(unsigned int i = 0; i < SCREEN_NB; i++){
    memset(&screens[i], 0, HEIGHT * WIDTH * 2);
    memset(&indexes[i], 0, 1);
    clear_screen(screens[i].screen);
    print_k(PINK, "42! - Screen n ", screens[i].screen, i);
    putkey(PINK, (char)((i + 1) + 48), screens[i].screen, i);
    putkey(PINK, '\n', screens[i].screen, i);
  }
  	memcpy((void *)VIDEO, screens[0].screen, WIDTH * HEIGHT * 2);
	if (active_screen == 0){
		print_k(WHITE, " !!! WELCOME 2 THE GROUNDBREAKING KERNSHELL !!!\n", (char *)VIDEO, active_screen);
		print_k(GREEN, " !!! Type reboot to send triple fault\n", (char *)VIDEO, active_screen);
		minishell_that(WHITE, '>', (char *)VIDEO);
	}
  	return ;
}

void kmain(void)
{
	init_data();
	// init_gdt();
	// print_stack();
	while(1){
    	keyboard_routine();
  	}
	return;
}
