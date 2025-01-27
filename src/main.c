
#include "../include/minishell.h"

/**
 * @brief Sends for all variables that need to be defined
 */
void	init(t_mini *mini, char **envp)
{
	mini->envp = envp;
	setupenv(mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*test;

	char	*path;
	path = ft_strdup("man");

	(void)argc;
	(void)argv;
	init(&mini, envp);
	test = malloc(sizeof(char) * BUFFER_SIZE);
	while (1)
	{
		ft_printf("%s ~ MyShell> ", mini.user);
		test = get_next_line(1);
		if (ft_strncmp(test, "pwd", 3) == 0)
			pwd(&mini);
		else if (ft_strncmp(test, "cd", 2) == 0)
			cd(path);
	}
	return (0);
}