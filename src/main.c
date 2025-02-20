/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:04:03 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/20 14:24:51 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_entry(char *entry)
{
	if (entry == NULL)
		return (ft_printf("exit\n"), cleanup_history(), 1);
	if (check_signal_interrupt())
		return (free(entry), 2);
	if (*entry)
		add_to_history(entry);
	return (0);
}

static void	process_input(t_mini *mini, char *entry, char **envp)
{
	if (entry && *entry)
	{
		parsing(entry, mini);
		execute(mini, envp);
		free_token_list(mini);
	}
	free(entry);
}

/**
 * @brief Sends for all variables that need to be defined
 * @param t_mini *mini
 * @param char **envp
 */
int	init(t_mini *mini, char **envp)
{
	mini->exit = 0;
	mini->token = NULL;
	mini->backup = NULL;
	mini->envp = copy_env(envp);
	init_readline_history();
	if (!mini->envp)
		return (mini->envp = NULL,
			mini->exit = 1, 0);
	if (!setup_signal_handlers())
		mini->exit = 1;
	setupenv(mini);
	return (0);
}

static void	shell_loop(t_mini *mini, char **envp)
{
	char	*entry;
	char	*prompt;
	int		ret;

	while (mini->exit == 0)
	{
		g_signo = 0;
		prompt = get_prompt(mini);
		if (!prompt)
			break ;
		entry = readline(prompt);
		free(prompt);
		ret = check_entry(entry);
		if (ret == 1)
			break ;
		if (ret == 2)
			continue ;
		process_input(mini, entry, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init(&mini, envp);
	shell_loop(&mini, envp);
	cleanup_history();
	return (free(mini.user), mini.exit);
}
