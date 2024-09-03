#include "kernel.h"
#include "keyboard_map.h"

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
	//out_port(0x20, 0x20);

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
    print_k(PINK, "42! J ARRIVE A ECRIRE EN MAJ\n");
	//init_idt();
	// // init keyboard - 0xFD is 11111101 - enables only IRQ1 (keyboard)
	//out_port(0x21 , 0xFD);
	// out_port(0x21 , 0xFD);
  
	while(1){
    keyboard_routine();
  }
	// print_k(YELLOW, "uh oh\n");
	return;
}
