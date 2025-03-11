/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:43:01 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/11 11:41:49 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "../../include/minishell.h"

int	g_signo;

static void	handle_signal()
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
int	setup_signal_handlers()
{
	struct sigaction	sa;
	
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL))
		return (0);
	if (sigaction(SIGQUIT, &sa, NULL))
		return (0);
	return (1);
}

void	reset_signals_for_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// int	check_signal_interrupt(void)
// {
// 	if (g_signo == SIGINT)
// 	{
// 		g_signo = 0;
// 		return (1);
// 	}
// 	return (0);
// }
