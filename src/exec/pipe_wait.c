/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:55:01 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/27 22:54:32 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_for_children(t_mini *mini, pid_t *pids)
{
	int	i;
	int	status;

	void (*old_int)(int); //test
	i = 0;
	old_int = signal(SIGINT, SIG_IGN);
	while (i <= mini->pipe_num)
	{
		waitpid(pids[i], &status, 0);
		if (WIFSIGNALED(status))
			mini->ret = 128 + WTERMSIG(status);
		i++;
	}
	signal(SIGINT, old_int);
	return (mini->ret);
}
