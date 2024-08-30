#include "kernel.h"
#include "keyboard_map.h"

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

	/* write EOI */
	print_k(YELLOW, "INSIDE THE KEYBOARD ROUTINE FUNC\n");
	out_port(0x20, 0x20);
	/* Read from the keyboard's data buffer */
	scancode = in_port(KEY_STATUS);
	/* Lowest bit of key status will be set if buffer is not empty */
	if (scancode & 0x01){
		keycode = in_port(KEY_PRESSED);
		if(keycode < 0)
			return;
		putkey(GREEN, keyboard_map[keycode]);
	}
}


void kmain(void)
{
	clear_screen();
    print_k(PINK, "42\n");
	init_idt();

	
	while(1){

	};
	return;
}