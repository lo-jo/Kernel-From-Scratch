#include "kernel.h"


// size_t strlen(const char* str) 
// {
// 	size_t len = 0;
// 	while (str[len])
// 		len++;
// 	return len;
// }

// https://wiki.osdev.org/Printing_To_Screen
void write_string(int colour, const char *string){
    volatile char *video = (volatile char*)VIDEO;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}


void clear_screen(int color){
	volatile char *video = (volatile char*)VIDEO;
	unsigned int j = 0;

	// there are 25 lines each of 80 columns; each element takes 2 bytes
	while(j < 80 * 25 * 2) {
		/* blank character */
		video[j] = ' ';
		/* attribute-byte - light grey on black screen */
		video[j+1] = color; 		
		j += 2;
	}
}
void kmain(void)
{
	clear_screen(0x05);
    write_string(PINK, "42");

	return;
}