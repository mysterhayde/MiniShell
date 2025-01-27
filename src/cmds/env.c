#include "../../include/minishell.h"

/**
 * @brief prints all the environment variables
 * @returns 0 on success, 1 on fail
 */
int	env(t_mini *mini)
{
	if (ft_print_chartable(mini->envp) == 0)
		return (0);
	return (1);
}
