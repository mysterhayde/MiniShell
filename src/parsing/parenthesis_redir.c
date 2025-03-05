/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:23:05 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/05 18:23:05 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Execute a parenthesized expression with redirections
 * @param mini Shell state
 * @param token Token starting with LEFT_PAREN
 * @return Execution result
 */
int	exec_paren_with_redir(t_mini *mini, t_token *token)
{
	int		saved_fd[2];
	int		ret;

	save_std_fds(saved_fd);
	if (apply_redir(token))
		return (restore_std_fds(saved_fd), 1);
	ret = exec_paren_expr(mini, token);
	restore_std_fds(saved_fd);
	return (ret);
}

/**
 * @brief Execute a command with logical operators and redirections
 * @param mini Shell state
 * @param token Token containing the command
 * @return Exit status
 */
int	exec_logical_with_redir(t_mini *mini, t_token *token)
{
	int		saved_fd[2];
	int		ret;

	save_std_fds(saved_fd);
	if (apply_redir(token))
		return (restore_std_fds(saved_fd), 1);
	ret = exec_logical_op_with_parens(mini, token);
	restore_std_fds(saved_fd);
	return (ret);
}
