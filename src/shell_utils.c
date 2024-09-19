#include "kernel.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int get_shell_index(unsigned int screen_nb){
	unsigned short index;

	/* equation for finding the index in a linear chunk of memory:
    *  Index = [(y * width) + x] */
	index = SHELL_LINE * 80 + indexes[screen_nb].pos_x;

	return index;
}

void  exec_command(const char *command_start){

  char  command[256];
  int i = 0;
  while (i < command_len - 1){
    command[i] = command_start[1 + (2 * i)];
    i++;
  }
  command[i] = '\0';
  indexes[active_screen].pos_x = 0;
  scroll();
  if (!ft_strncmp(command, "stack", command_len))
    print_stack_test();
  else if (!ft_strncmp(command, "reboot", command_len))
    send_reboot();
  else if (!ft_strncmp(command, "halt", command_len))
    halt();
  else if (!ft_strncmp(command, "sardines", command_len))
    ft_sardine();
  else if (!ft_strncmp(command, "help", command_len))
    ft_help();
  else {
    print_k(WHITE, "Command '", (char *)VIDEO, active_screen); 
    print_k(WHITE, command, (char *)VIDEO, active_screen); 
    print_k(WHITE, "' not found, type 'help' to list commands", (char *)VIDEO, active_screen); 
  }
}
