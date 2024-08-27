#include "kernel.h"
#include "keyboard_map.h"

unsigned char* memcpy(unsigned char *dstptr, const unsigned char *srcptr, int size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (int i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
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