#include "../../include/minishell.h"

void	getuser(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->envp[i] && ft_strnstr(mini->envp[i], "USER", 4) == 0)
	{
		(mini->envp)++;
		i++;
	}
	mini->user = ft_strdup(mini->envp[i] + 5);
}
void	setupenv(t_mini *mini)
{
	getuser(mini);
}
