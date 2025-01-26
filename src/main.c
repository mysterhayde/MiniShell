
#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		while (1)
		{
			ft_printf("MyShell> ");
			get_next_line(1);
		}
	return (0);
}