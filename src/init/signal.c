/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:43:01 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/31 10:32:59 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_fork_signal(int status)
{
	if (WTERMSIG(status) == SIGINT)
		write(STDERR_FILENO, "\n", 1);
	else if (WTERMSIG(status) == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	return (128 + WTERMSIG(status));
}

int	setup_signal_handlers_fork(void)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_ignore, NULL) == -1)
		return (1);
	return (0);
}

static void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signo = 1;
	}
}

int	setup_signal_handlers(t_mini *mini)
{
	struct sigaction	s_int;
	struct sigaction	s_quit;

	s_int.sa_handler = handle_signal;
	sigemptyset(&s_int.sa_mask);
	s_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &s_int, NULL) == -1)
		return (1);
	s_quit.sa_handler = SIG_IGN;
	sigemptyset(&s_quit.sa_mask);
	s_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &s_quit, NULL) == -1)
		return (1);
	if (g_signo > 0)
		mini->ret = g_signo;
	return (0);
}
