#include "kernel.h"

unsigned int pos_x = 0;
unsigned int pos_y = 0;

unsigned int  active_screen = 0;

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

    if(indexes[active_screen].pos_y >= 25)
    {
        /* select chunk of memory from screen */
        temp = indexes[active_screen].pos_y - 25 + 1;
        /* copy it into screen */
        memcpy((unsigned char *)VIDEO, (unsigned char *)VIDEO + temp * 80 * 2, (25 - temp) * 80 * 2);

        /* set last line to blank */
        // memset ((unsigned short *)VIDEO + (25 - temp) * 80, blank, 80 * 2);
        unsigned char* buffer = (unsigned char *)VIDEO + (25 - temp) * 80 * 2;
        for (int i = 0; i < 80 *2; i+=2){
            buffer[i] = ' ';
            buffer[i+1] = WHITE;
        }
        indexes[active_screen].pos_y = 25 - 1;
    }
}

void update_cursor(void)
{
    unsigned idx;
    idx = get_index(active_screen);

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
  memcpy(screens[active_screen].screen, (void *)VIDEO, WIDTH * HEIGHT);
  active_screen = screen_nb;
  memcpy((void *)VIDEO, screens[active_screen].screen, WIDTH * HEIGHT);
  return ; 
}
