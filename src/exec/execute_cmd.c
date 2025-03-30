/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:13:51 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/30 23:01:05 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Check if command has parentheses
 * @param token Token to check
 * @return TRUE if contains parentheses, FALSE otherwise
 */
// static t_bool	has_parentheses_check(t_token *token)
// {
// 	t_token	*current;

// 	current = token;
// 	while (current)
// 	{
// 		if (current->type == LEFT_PAREN || current->type == RIGHT_PAREN)
// 			return (TRUE);
// 		current = current->next;
// 	}
// 	return (FALSE);
// }

/**
 * @brief Process first part before executing command
 * @param mini Shell state
 * @return 0 on success, 1 on failure
 */
static int	pre_process(t_mini *mini)
{
	if (scan_and_execute_all_heredocs(mini))
		return (1);
	return (0);
}

/**
 * @brief Execute based on command type (exit)
 * @param mini Shell state
 * @return TRUE if command was exit, FALSE otherwise
 */
static t_bool	execute_exit(t_mini *mini)
{
	if (ft_strmincmp(mini->token->cmd[0], "exit", 4) == 0)
	{
		check_string(mini, mini->token);
		return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief Execute based on command type (complex commands)
 * @param mini Shell state
 */
static void	execute_complex(t_mini *mini)
{
	if (has_parentheses(mini->token))
	{
		if (is_parenthesis_cmd(mini->token))
			mini->ret = exec_parenthesis(mini);
		else
			mini->ret = exec_logical_with_redir_heredoc(mini, mini->token);
	}
	else if (has_logical_ops(mini->token))
		mini->ret = exec_logical_ops_heredoc(mini, mini->token);
	else if (mini->is_pipe)
		mini->ret = minipipe_with_heredoc(mini);
	else
		mini->ret = check_string(mini, mini->token);
}

int	check_all_file_permission(t_token *token)
{
	while (token)
	{
		if (token->type == RDIT && token->cmd[0][0] == '<')
		{
			if (access(token->next->cmd[0], F_OK) == -1)
				return (file_access_failed(token->next->cmd[0]), 1);
			if (access(token->next->cmd[0], R_OK) == -1)
				return (file_access_failed(token->next->cmd[0]), 1);
		}
		if (token->type == RDIT && token->cmd[0][0] == '>')
		{
			if (access(token->next->cmd[0], F_OK) == 0)
			{
				if (access(token->next->cmd[0], W_OK) == -1)
					return (file_access_failed(token->next->cmd[0]), 1);
			}
		}
		token = token->next;
	}
	return (0);
}

/**
 * @brief Calls of expansion of argument(s) and then manages
 * builtin or bin commands
 * @param t_mini *mini
 * @details It checks for pipes anywhere in the input because if there's a pipe
 * everything needs to be executed inside a fork. If there's no pipe
 * builtin commands need to be executed without piping.
 */
void	execute(t_mini *mini)
{
	if (!mini->token || !mini->token->cmd)
		return ;
	if (check_all_file_permission(mini->backup))
	{
		mini->ret = 1;
		return ;
	}
	if (pre_process(mini))
	{
		mini->ret = 1;
		return ;
	}
	if (!execute_exit(mini))
		execute_complex(mini);
	free_heredoc_arrays(mini);
}
