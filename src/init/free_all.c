/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:18:45 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/27 22:38:07 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Frees pipe resources allocated in t_pipe structure
 * @param p Pipe strucutre containing resources to free
 */
void	free_pipe_resources(t_pipe *p)
{
	if (p->pipe_fds)
		free(p->pipe_fds);
	if (p->pids)
		free(p->pids);
	p->pipe_fds = NULL;
	p->pids = NULL;
}

void	free_all(t_mini *mini)
{
	cleanup_history();
	if (!mini)
		return ;
	if (mini->heredoc_fds)
		free(mini->heredoc_fds);
	if (mini->heredoc_tokens)
		free(mini->heredoc_tokens);
	if (mini->user)
		free(mini->user);
	if (mini->token || mini->backup)
		free_token_list(mini);
	if (mini->envp)
		free_env_arr(mini->envp);
}

/**
 * @brief Safe exit function that ensures cleanup before exiting
 * @param mini Shell state
 * @param exit_code Exit code to return
 */
void	safe_exit(t_mini *mini, int exit_code)
{
	free_all(mini);
	cleanup_history();
	exit(exit_code);
}
