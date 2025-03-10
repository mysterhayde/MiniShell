/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:04:03 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/05 20:02:30 by cbopp            ###   ########.fr       */
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

static void	process_input(t_mini *mini, char *entry)
{
	if (entry && *entry)
	{
		if (!parsing(entry, mini))
			execute(mini);
		free_token_list(mini);
	}
	free(entry);
}

/**
 * @brief Sends for all variables that need to be defined
 * @param t_mini *mini
 * @param char **envp
 */
void	init(t_mini *mini, char **envp)
{
	mini->exit = 0;
	mini->token = NULL;
	mini->backup = NULL;
	mini->envp = NULL;
	init_readline_history();
	if (!setup_signal_handlers())
		mini->exit = 1;
	setupenv(mini, envp);
}

static void	shell_loop(t_mini *mini)
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
		process_input(mini, entry);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init(&mini, envp);
	shell_loop(&mini);
	free_all(&mini);
	return (0);
}
