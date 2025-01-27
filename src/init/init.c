#include "../../include/minishell.h"

void	getcurpath(t_mini *mini)
{
	char	buf[BUFFER_SIZE];

	mini->cur_path = getcwd(buf, BUFFER_SIZE);
	if (mini->cur_path != NULL)
		return ;
	perror("Pwd");
}

static void	getuser(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->envp[i] && ft_strnstr(mini->envp[i], "USER=", 5) == 0)
	{
		i++;
	}
	mini->user = ft_strdup(mini->envp[i] + 5);
}

void	setupenv(t_mini *mini)
{
	getuser(mini);
	getcurpath(mini);
}
