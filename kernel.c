#include "kernel.h"
#include "keyboard_map.h"

struct s_index indexes[SCREEN_NB];
struct s_screens screens[SCREEN_NB];

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
			putshell(WHITE, keyboard_map[keycode], (char *)VIDEO);
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
	print_k(PINK, "Press fn + [1] for kernshell\n", screens[i].screen, i);
	print_k(PINK, "Press fn + [2 - 9] to switch screens\n", screens[i].screen, i);
  }
  	memcpy((void *)VIDEO, screens[0].screen, WIDTH * HEIGHT * 2);
	if (active_screen == 0){
		print_k(WHITE, " !!! WELCOME 2 THE GROUNDBREAKING KERNSHELL !!!\n", (char *)VIDEO, active_screen);
		print_k(GREEN, " !!! Type reboot to send triple fault\n", (char *)VIDEO, active_screen);
		putshell(WHITE, '>', (char *)VIDEO);
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
