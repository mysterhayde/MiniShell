
#include "../include/minishell.h"

void	init(t_mini *mini, char **envp)
{
	mini->envp = envp;
	setupenv(mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init(&mini, envp);
	while (1)
	{
		ft_printf("%s ~ MyShell> ", mini.user);
		get_next_line(1);
	}
	return (0);
}