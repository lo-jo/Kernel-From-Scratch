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

void  exec_command(const char *command){

  if (!ft_strncmp(command, "print_stack", command_len))
    print_stack_test();
  else if (!ft_strncmp(command, "reboot", command_len))
    print_k(WHITE, "reboot", (char *)VIDEO, active_screen);
  else if (!ft_strncmp(command, "halt", command_len))
    print_k(WHITE, "halt", (char *)VIDEO, active_screen);
  else if (!ft_strncmp(command, "sardines", command_len))
    print_k(WHITE, "sardines", (char *)VIDEO, active_screen);
  else if (!ft_strncmp(command, "help", command_len))
    print_k(WHITE, "help", (char *)VIDEO, active_screen);
  else
    print_k(WHITE, "Command not found, type 'help' to list commands", (char *)VIDEO, active_screen); 
}
