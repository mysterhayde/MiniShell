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

	char	*path;
	path = ft_strdup("/home");

	(void)argc;
	(void)argv;
	init(&mini, envp);
	while (TRUE)
	{
		ft_printf("%s ", mini.user);
		test = readline("~ MyShell> ");
		if (test == NULL)
			return (0);
		if (ft_strmincmp(test, "pwd", 3) == 0)
			pwd(&mini);
		else if (ft_strmincmp(test, "export", 6) == 0)
			export(mini);
		else if (ft_strmincmp(test, "cd", 2) == 0)
			cd(path);
		else if (ft_strmincmp(test, "env", 3) == 0)
			env(&mini);
		else if (ft_strmincmp(test, "echo", 4) == 0)
			echo(TRUE, mini.user);
		else if (ft_strmincmp(test, "exit", 4) == 0)
			exit_builtin(1);
	}
	return (0);
}
