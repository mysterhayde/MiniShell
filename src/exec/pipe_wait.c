/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:55:01 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/18 17:04:57 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_for_children(t_mini *mini, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i <= mini->pipe_num)
	{
		waitpid(pids[i], &status, 0);
		if (WIFSIGNALED(status))
			mini->ret = 128 + WTERMSIG(status);
		i++;
	}
	return (mini->ret);
}
