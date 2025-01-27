
#include "../include/minishell.h"

void	init(t_mini *mini, char **envp)
{
	mini->envp = envp;
	setupenv(mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*test;

	(void)argc;
	(void)argv;
	init(&mini, envp);
	test = malloc(sizeof(char) * BUFFER_SIZE);
	while (1)
	{
		ft_printf("%s ~ MyShell> ", mini.user);
		test = get_next_line(1);
		if (ft_strncmp(test, "pwd", 3) == 0)
			pwd();
	}
	return (0);
}