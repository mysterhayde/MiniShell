/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:29:10 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/25 13:28:05 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Count the number of pipe tokens in a token list
 * @param token token list to count
 * @return number of pipe tokens
 */
static int	count_pipes(t_token *token)
{
	t_token	*current;
	int		count;

	count = 0;
	current = token;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

/**
 * @brief Creates a command sublist from start to (but not including) end
 * This function creates a deep copy of the token list
 * @param start starting token
 * @param end ending token (not included)
 * @return new token list
 */
t_token	*create_command_sublist(t_token *start, t_token *end)
{
	t_token	*current;
	t_token	*sublist;
	t_token	*new_token;
	t_token	*last;

	sublist = NULL;
	last = NULL;
	current = start;
	while (current != end && current)
	{
		new_token = copy_token(current);
		if (!new_token)
			return (free_tokens(sublist), NULL);
		if (!sublist)
			sublist = new_token;
		else
			last->next = new_token;
		last = new_token;
		current = current->next;
	}
	return (sublist);
}

/**
 * @brief Executes a command sublist
 * @param mini shell state
 * @param sublist token list to execute
 * @return ocmmand execution status
 */
int	exec_sublist(t_mini *mini, t_token *sublist)
{
	t_state	state;
	int		ret;
	int		has_pipe;

	save_exec_state(mini, &state);
	mini->token = sublist;
	has_pipe = count_pipes(sublist);
	if (has_pipe > 0)
	{
		mini->is_pipe = TRUE;
		mini->pipe_num = has_pipe;
		ret = minipipe_with_heredoc(mini);
	}
	else
	{
		mini->is_pipe = FALSE;
		if (has_logical_ops(sublist))
			ret = exec_logical_ops_heredoc(mini, sublist);
		else
			ret = check_string(mini, sublist);
	}
	restore_exec_state(mini, &state);
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
