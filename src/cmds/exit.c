#include "../../include/minishell.h"

void	exit_builtin(int n)
{
	ft_printf("exit\n");
	exit(n);
}
