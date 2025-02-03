#include "../../include/minishell.h"

void	exit_builtin(t_mini *mini)
{
	ft_printf("exit\n");
	exit(mini->exit);
}
