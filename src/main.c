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
	char	*entry;

	char	*path;
	path = ft_strdup("/home");
	mini.token = NULL;
	mini.backup = NULL;
	(void)argc;
	(void)argv;
	init(&mini, envp);
	while (TRUE)
	{
		ft_printf("%s ", mini.user);
		entry = readline("~ MyShell> ");
		if (entry == NULL)
			return (0);
		parsing(entry, &mini);
		if (ft_strmincmp(entry, "pwd", 3) == 0)
			pwd(&mini);
		//else if (ft_strmincmp(test, "export", 6) == 0)
		//	export(mini);
		else if (ft_strmincmp(entry, "cd", 2) == 0)
			cd(path);
		else if (ft_strmincmp(entry, "env", 3) == 0)
			env(&mini);
		else if (ft_strmincmp(entry, "echo", 4) == 0)
			echo(TRUE, mini.user);
		else if (ft_strmincmp(entry, "exit", 4) == 0)
			exit_builtin(1);
		// if (entry)
		// 	free(entry);
		free_token_list(&mini);
	}
	return (0);
}
