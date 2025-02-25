/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:11:15 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/25 16:24:14 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Skips redirection tokens in the token list
 * @param token token to start from
 * @return pointer to the first non-redirection token
 */
t_token	*skip_redirections(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == CMD)
			return (current);
		if (current->type == RDIT && current->next)
			current = current->next->next;
		else
			current = current->next;
	}
	return (NULL);
}

/**
 * @brief Executes a command with redirections
 * @param mini shell state
 * @param token token containing the command
 * @return exit status
 */
int	exec_redirections(t_mini *mini, t_token *token)
{
	int		saved_fd[2];
	int		ret;
	t_token	*cmd_token;

	save_std_fds(saved_fd);
	if (apply_redir(token))
		return (restore_std_fds(saved_fd), 1);
	cmd_token = skip_redirections(token);
	if (!cmd_token)
		return (restore_std_fds(saved_fd), 0);
	if (is_builtin(cmd_token->cmd[0]))
		ret = exec_builtin(mini, cmd_token->cmd);
	else
		ret = exec_bin(mini, cmd_token->cmd);
	restore_std_fds(saved_fd);
	return (ret);
}
