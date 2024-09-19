#include "kernel.h"

unsigned int  active_screen = 0;

void clear_line(char *screen, unsigned int line)
{
	unsigned short *index;
	index = (unsigned short *)screen + line * 80;
	for (int i = 0; i < 80 * 2; i += 2) {
			screen[line * 80 * 2 + i] = ' ';
			screen[line * 80 * 2 + i + 1] = WHITE;
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

int get_index(unsigned int screen_nb){
	unsigned short index;

	/* equation for finding the index in a linear chunk of memory:
    *  Index = [(y * width) + x] */
	index = indexes[screen_nb].pos_y * 80 + indexes[screen_nb].pos_x;

	return index;
}

void scroll(void)
{
    unsigned temp;
    unsigned int line = 24;

    if (active_screen == 0)
      line = SHELL_LINE;
    if(indexes[active_screen].pos_y >= line)
    {
        /* select chunk of memory from screen */
        temp = indexes[active_screen].pos_y - line + 1;
        /* copy it into screen */
        memcpy((unsigned char *)VIDEO, (unsigned char *)VIDEO + temp * 80 * 2, (line - temp) * 80 * 2);

        /* set last line to blank */
        // memset ((unsigned short *)VIDEO + (line - temp) * 80, blank, 80 * 2);
        unsigned char* buffer = (unsigned char *)VIDEO + (line - temp) * 80 * 2;
        for (int i = 0; i < 80 *2; i+=2){
            buffer[i] = ' ';
            buffer[i+1] = WHITE;
        }
        indexes[active_screen].pos_y = line - 1;
    }
}

void update_cursor(void)
{
    unsigned idx;
    if (active_screen == 0)
        idx = SHELL_LINE * 80 + indexes[active_screen].pos_x;
    else   
        idx = indexes[active_screen].pos_y * 80 + indexes[active_screen].pos_x;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'.*/
    out_port(0x3D4, 14);
    out_port(0x3D5, idx >> 8);
    out_port(0x3D4, 15);
    out_port(0x3D5, idx);
}

void switch_screen(unsigned int screen_nb)
{
  if (active_screen == screen_nb)
    return ;
  memcpy(screens[active_screen].screen, (void *)VIDEO, WIDTH * HEIGHT * 2);
  active_screen = screen_nb;
  memcpy((void *)VIDEO, screens[active_screen].screen, WIDTH * HEIGHT * 2);
  return ; 
}
