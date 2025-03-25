/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:40:34 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/25 17:11:58 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Handles errors when expanding variables
 * @param cmd Command containing the variables
 * @return Error code (1)
 */
static int	handle_var_error(char *cmd)
{
	ft_putstr_fd("minishell: error expanding variable in command: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

/**
 * @brief TRansforms all variables and quotes in a token's commands
 * @param current Token to transform
 * @param envp Environment variables
 * @param return_code Last command's return code
 * @return 0 on success, error code on failure
 */
int	transform_string(t_token *current, char **envp, int return_code)
{
	int		j;
	int		error;

	j = 0;
	error = 0;
	while (current->cmd[j])
	{
		current->cmd[j] = search_variable(current->cmd[j], envp, &error);
		if (error || !current->cmd[j])
			return (handle_var_error(current->cmd[0]));
		current->cmd[j] = search_error_code(return_code, current->cmd[j]);
		if (strchr(current->cmd[j], '\"') || strchr(current->cmd[j], '\''))
		{
			current->cmd[j] = clean_quote(current->cmd[j]);
			if (!current->cmd[j])
				return (handle_var_error(current->cmd[0]));
		}
		j++;
	}
	return (0);
}

/**
 * @brief Processes a command token, expanding variables and executing
 * @param mini Shell state
 * @param cmd_token Comand token to process
 * @return Return code of the executed command
 */
int	check_string(t_mini *mini, t_token *cmd_token)
{
	int	ret;

	cmd_token->cmd = search_wildcard(cmd_token);
	if (!cmd_token->cmd)
		return (ERR_GENERAL);
	if (transform_string(cmd_token, mini->envp, mini->ret) != 0)
		return (ERR_GENERAL);
	fix_index(cmd_token);
	ret = exec_redirections_with_heredoc(mini, cmd_token);
	mini->ret = ret;
	return (ret);
}
