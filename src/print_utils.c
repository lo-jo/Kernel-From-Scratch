#include "kernel.h"

void ft_sardine(void)
{
	print_k(WHITE, " __      ___              _         \n", (char *)VIDEO, active_screen);
	print_k(WHITE, " \\ \\    / (_)            | |        \n", (char *)VIDEO, active_screen);
	print_k(WHITE, "  \\ \\  / / ___   ____ _  | | __ _   \n", (char *)VIDEO, active_screen);
	print_k(WHITE, "   \\ \\/ / | \\ \\ / / _` | | |/ _` |  \n", (char *)VIDEO, active_screen);
	print_k(WHITE, "    \\  /  | |\\ V / (_| | | | (_| |  \n", (char *)VIDEO, active_screen);
	print_k(WHITE, "     \\/   |_| \\_/ \\__,_| |_|\\__,_|  \n", (char *)VIDEO, active_screen);
	print_k(WHITE, "                   | (_)            \n", (char *)VIDEO, active_screen);
	print_k(WHITE, "  ___  __ _ _ __ __| |_ _ __   __ _ \n", (char *)VIDEO, active_screen);
	print_k(WHITE, " / __|/ _` | '__/ _` | | '_ \\ / _` |\n", (char *)VIDEO, active_screen);
	print_k(WHITE, " \\__ \\ (_| | | | (_| | | | | | (_| |\n", (char *)VIDEO, active_screen);
	print_k(WHITE, " |___/\\__,_|_|  \\__,_|_|_| |_|\\__,_|\n", (char *)VIDEO, active_screen);
	print_k(WHITE, "  | (_) |                           \n", (char *)VIDEO, active_screen);
	print_k(WHITE, "  | |_| |__  _ __ ___     <*))))><  \n", (char *)VIDEO, active_screen);
	print_k(WHITE, "  | | | '_ \\| '__/ _ \\        <*))))><\n", (char *)VIDEO, active_screen);
	print_k(WHITE, "  | | | |_) | | |  __/     <*))))><  \n", (char *)VIDEO, active_screen);
	print_k(WHITE, "  |_|_|_.__/|_|  \\___|             \n", (char *)VIDEO, active_screen);
}

void  ft_help(void)
{
  print_k(WHITE, "'clear' : clears the screen\n", (char *)VIDEO, active_screen);
  print_k(WHITE, "'halt' :  halt the CPU \n", (char *)VIDEO, active_screen);
  print_k(WHITE, "'reboot' :  reboot the kernel \n", (char *)VIDEO, active_screen);
  print_k(WHITE, "'stack' :  print the stack frames \n", (char *)VIDEO, active_screen);
  print_k(WHITE, "'sardines' : print the Anticapitalist Independentist Sardines Union's\n", (char *)VIDEO, active_screen);
  print_k(WHITE, "slogan (sponsor of the project)\n", (char *)VIDEO, active_screen);
}


// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⢀⣠⡤⠶⠒⠛⠋⢉⣉⣉⣉⣉⣉⣉⡉⠙⠛⠒⠶⢤⣄⡀⠀⠀⠀⠀
// ⠀⠀⣠⣾⠋⣁⣤⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣤⣈⠙⣷⣄⠀⠀
// ⠀⢸⣿⣧⡐⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢂⣼⣿⡇⠀
// ⠀⢀⠙⠿⣿⣦⣌⣉⣛⠛⠛⠛⠛⠻⠿⠿⠟⠛⠛⠛⠛⣛⣉⣡⣴⣿⠿⠋⡀⠀
// ⠀⢸⣷⣦⣄⣉⠙⠛⠻⠿⠿⢿⣶⣶⣶⣶⣶⣶⡿⠿⠿⠟⠛⠋⣉⣠⣴⣾⡇⠀
// ⠀⢸⣿⣿⣿⣿⣿⣿⣶⣶⣦⣤⣤⣤⣤⣤⣤⣤⣤⣴⣶⣶⣿⣿⣿⣿⣿⣿⡇⠀
// ⠀⢸⣿⣿⣿⡏⠻⣿⣿⣿⣿⣿⣿⡿⠿⠿⠿⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀
// ⠀⢸⣿⣿⣿⡇⠀⠀⠙⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⢿⣿⣿⣿⡇⠀
// ⠀⢸⣿⣿⣿⡇⠀⠀⣠⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣿⡇⠀
// ⠀⠀⠻⢿⣿⣇⣴⣿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣶⣶⣶⣿⣿⣿⣿⣿⣿⡿⠟⠀⠀
// ⠀⠀⠀⠀⠉⠛⠻⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠟⠛⠉⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀

void putshell(int color, char c, char *screen)
{
	unsigned short *index;
	index = (unsigned short *)screen + SHELL_LINE * 80 + indexes[0].pos_x;

	if (c == '\b'){
		if (indexes[active_screen].pos_x != 0){
			if (indexes[active_screen].pos_x != 1){
				indexes[active_screen].pos_x--;
        index -= 1;
			}
			c = ' ';
			color = WHITE;
			*index = c | color << 8;
      if (command_len > 1)
        command_len--;
		}
	}
	else if (c < 0  && c > -10)
    	switch_screen((unsigned int)(-c - 1));
	else if (c == '\n'){
    exec_command((char *)VIDEO + (get_shell_index(0) * 2) - (command_len * 2) + 1);
    command_len = 0;
		clear_line(screen, SHELL_LINE);
    indexes[active_screen].pos_x = 0;
		indexes[active_screen].pos_y++;
		putshell(WHITE, '>', screen);
	}
	else{
    command_len++;
		*index = c | color << 8;
		indexes[active_screen].pos_x++;
	}
	if (indexes[active_screen].pos_x >= WIDTH){
    command_len = 1;
		clear_line(screen, SHELL_LINE);
		indexes[active_screen].pos_x = 0;
		indexes[active_screen].pos_y++;
		putshell(WHITE, '>', screen);
	}
	if (indexes[active_screen].pos_y >= HEIGHT){
		scroll();
	}
	update_cursor();
}

void print_hex(unsigned int value, int color, int size){
	char *hex = "0123456789abcdef";
	char buffer[9];
	int i;

	buffer[size] = 0;
	for(i = size - 1; i >= 0; i--){
		buffer[i] = hex[value & 0xF];
		value >>= 4;
	}
	print_k(color, buffer, (char *)VIDEO, active_screen);
}

void  hexdump_k(uint32_t stack_top, int limit){

  char  *address = (char *)stack_top;
  int i;
  char *start_point;

  for (i = 0; stack_top < limit; i++)
  {
    if (i % 16 == 0)
    {
      if (i != 0)
      {
        start_point = address - 16;
        putkey(WHITE, ' ', (char *)VIDEO, active_screen);
        putkey(WHITE, ' ', (char *)VIDEO, active_screen);
        for (int y = 0; y < 16; y++)
        {
          if (start_point[y] <= 32 || start_point[y] >= 126)
            putkey(WHITE, '.', (char *)VIDEO, active_screen);
          else
            putkey(WHITE, start_point[y], (char *)VIDEO, active_screen);
        }
        print_k(WHITE, "\n", (char *)VIDEO, active_screen);
      }
	    print_k(PINK, "0x", (char *)VIDEO, active_screen);
      print_hex((unsigned int)stack_top, PINK, 8);
	    print_k(PINK, ": ", (char *)VIDEO, active_screen);
    }
    print_k(WHITE, " ", (char *)VIDEO, active_screen);
    print_hex(*address, WHITE, 2);
    stack_top++;
    address++;
  }
  return ;
}

void  print_stack_test(void)
{
  uint32_t *ebp;
  uint32_t *esp;

  //hexdump_k(*esp, (*ebp - *esp));
  asm volatile (
        "movl %%ebp, %0 \n\t"  // Move the value of EBP into the memory location of ebp_ptr
        "movl %%esp, %1 \n\t"  // Move the value of ESP into the memory location of esp_ptr
        : "=r" (*ebp), "=r" (*esp)
  );
  //trace_stack((unsigned long *)esp, (unsigned long *)ebp);
  hexdump_k(*esp, *ebp);
  print_k(WHITE, "\n", (char *)VIDEO, active_screen);
  return ;
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
