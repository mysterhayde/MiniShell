
#include "../include/minishell.h"

void	init(t_mini *mini, char **envp)
{
	mini->envp = envp;
	setupenv(mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	init(&mini, envp);
	while (1)
	{
		ft_printf("MyShell> %s, %s", argv[0], envp[0]);
		get_next_line(1);
	}
	return (0);
}