#include "../include/minishell.h"

/**
 * @brief Sends for all variables that need to be defined
 * @param t_mini *mini
 * @param char **envp
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

	(void)argc;
	(void)argv;
	init(&mini, envp);
	while (mini.exit == 0)
	{
		ft_printf("%s ", mini.user);
		test = readline("~ MyShell> ");
		parsing(test, &mini);
	}	

	// 	ft_printf("%s ", mini.user);
	// 	test = readline("~ MyShell> ");

	return (0);
}
