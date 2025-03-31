/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:55:01 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/31 10:43:14 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_for_children(t_mini *mini, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	setup_signal_handlers_fork();
	while (i <= mini->pipe_num)
	{
		waitpid(pids[i], &status, 0);
		if (WIFSIGNALED(status))
			mini->ret = handle_fork_signal(status);
		i++;
	}
	// setup_signal_handlers(mini);
	return (mini->ret);
}
