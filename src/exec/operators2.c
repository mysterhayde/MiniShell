/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:29:10 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/25 16:59:25 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Executes a command with logical operators
 * @param mini shell state
 * @param token token containing the command
 * @return exit status
 */
int	exec_logical_ops(t_mini *mini, t_token *token)
{
	t_token	*op;
	t_token	*sublist;
	int		ret;

	op = find_next_logical_op(token);
	if (!op)
		return (exec_redirections(mini, token));
	sublist = create_command_sublist(token, op);
	if (!sublist)
		return (1);
	ret = exec_redirections(mini, sublist);
	free_tokens(sublist);
	if (op->type == AND_OP)
	{
		if (ret == 0)
			return (exec_logical_ops(mini, op->next));
		return (ret);
	}
	else if (op->type == OR_OP)
	{
		if (ret != 0)
			return (exec_logical_ops(mini, op->next));
		return (ret);
	}
	return (ret);
}

/**
 * @brief Copy a token
 * @param token token to copy
 * @return new token
 */
t_token	*copy_token(t_token *token)
{
	t_token	*new_token;
	int		i;
	int		len;

	if (!set(&new_token, malloc(sizeof(t_token))))
		return (NULL);
	new_token->type = token->type;
	new_token->expand = token->expand;
	new_token->next = NULL;
	if (!token->cmd)
		return (set(&new_token->cmd, NULL), new_token);
	len = 0;
	while (token->cmd[len])
		len++;
	new_token->cmd = malloc(sizeof(char *) * (len + 1));
	if (!new_token->cmd)
		return (free(new_token), NULL);
	i = -1;
	while (++i < len)
		new_token->cmd[i] = ft_strdup(token->cmd[i]);
	new_token->cmd[i] = NULL;
	return (new_token);
}

/**
 * @brief Free a token list
 * @param token list to be free
 */
void	free_tokens(t_token *token)
{
	t_token	*current;
	t_token	*next;
	int		i;

	current = token;
	while (current)
	{
		next = current->next;
		if (current->cmd)
		{
			i = 0;
			while (current->cmd[i])
				free(current->cmd[i++]);
			free(current->cmd);
		}
		free(current);
		current = next;
	}
}
