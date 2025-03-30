/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:04:03 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/30 14:36:06 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signo = 0;

int	check_entry(char *entry, t_mini *mini)
{
	if (entry == NULL)
		return (ft_printf("exit\n"), cleanup_history(), 1);
	if (*entry)
		add_to_history(mini, entry);
	return (0);
}

static void	process_input(t_mini *mini, char *entry)
{
	if (entry && *entry)
	{
		reset_error_reporting();
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
	mini->ret = 0;
	mini->exit = 0;
	mini->envp = NULL;
	mini->user = NULL;
	mini->token = NULL;
	mini->backup = NULL;
	mini->last_cmd = NULL;
	mini->isheredoc = FALSE;
	mini->heredoc_fds = NULL;
	mini->heredoc_tokens = NULL;
	mini->heredoc_count = 0;
	setupenv(mini, envp);
	init_readline_history(mini);
	if (setup_signal_handlers(mini))
	{
		mini->exit = 1;
		mini->ret = 130;
	}
}

static void	shell_loop(t_mini *mini)
{
	char	*entry;
	char	*prompt;
	int		ret;

	setup_signal_handlers(mini);
	while (mini->exit == 0)
	{
		prompt = get_prompt(mini);
		if (!prompt)
			break ;
		entry = readline(prompt);
		free(prompt);
		if (g_signo == 1)
		{
			mini->ret = 130;
			g_signo = 0;
		}
		ret = check_entry(entry, mini);
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
	return (mini.ret);
}
