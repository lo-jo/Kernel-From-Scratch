#include "kernel.h"

struct s_index indexes[SCREEN_NB];
struct s_screens screens[SCREEN_NB];

void  init_data(void)
{
  for(unsigned int i = 0; i < SCREEN_NB; i++){
    memset(&screens[i], 0, HEIGHT * WIDTH);
    memset(&indexes[i], 0, 1);
    clear_screen(screens[i].screen);
    print_k(PINK, "42! - Screen n ", screens[i].screen, i);
    putkey(PINK, (char)((i + 1) + 48), screens[i].screen, i);
    putkey(PINK, '\n', screens[i].screen, i);
  }
  memcpy((void *)VIDEO, screens[0].screen, WIDTH * HEIGHT);
  return ;
}
