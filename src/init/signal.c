/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:43:01 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/11 14:04:35 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../../include/minishell.h"

int	g_signo;

static void	handle_signal()
{
	printf("signal_receved\n");
}

// void	handle_signal(int signo)
// {
// 	g_signo = signo;
// 	if (signo == SIGINT)
// 	{
// 		write(STDERR_FILENO, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

int	setup_signal_handlers(void)
{
	struct sigaction sa;
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0; 
	return (0);
}

void	reset_signals_for_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	check_signal_interrupt(void)
{
	if (g_signo == SIGINT)
	{
		g_signo = 0;
		return (1);
	}
	return (0);
}
