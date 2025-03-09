/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:12 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/09 14:57:05 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Frees all links in the token chain, as well 
 * 		  as the cmd array inside each node
 * @param t_mini *mini
 */
void	free_token_list(t_mini *mini)
{
	t_token	*current;
	t_token	*next;

	if (!mini->backup)
		return ;
	current = mini->backup;
	while (current)
	{
		next = current->next;
		free_cmd_arr(current->cmd);
		free(current);
		current = next;
	}
	mini->token = NULL;
	mini->backup = NULL;
}

static char	**increase_tab(char **tab, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (show_err_msg("malloc", "memory allocation failed"), NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
			return (free_tab(new_tab), (NULL));
		i++;
	}
	new_tab[i] = ft_strdup(str);
	if (!new_tab[i])
		return (free_tab(new_tab), NULL);
	new_tab[i + 1] = NULL;
	return (free_tab(tab), new_tab);
}

/**
 * @brief Create a new token node
 * @param str The command string
 * @param type The token type
 * @return The newly created token node
 */
static t_token	*new_token(char *str, int type, t_mini *mini)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		show_error_exit("malloc", "memory allocation failed", 1);
	new->cmd = malloc(sizeof(char *) * 2);
	if (!new->cmd)
		return (free(new), NULL);
	new->cmd[0] = ft_strdup(str);
	if (!new->cmd[0])
		return (free(new->cmd), free(new), NULL);
	new->cmd[1] = NULL;
	new->type = type;
	new->next = NULL;
	if (type == PIPE)
		mini->pipe_num++;
	return (new);
}

static void	create_first_node(t_mini *mini, char *str, int type)
{
	mini->token = new_token(str, type, mini);
	if (!mini->token)
		show_error_exit("malloc", "memory allocation failed", 1);
	mini->backup = mini->token;
}

/**
 * @brief add a node to the end of the linked list
 * @param str The command string
 * @param mini The minishell struct
 * @param type The token type
 */
void	add_last_token(char *str, t_mini *mini, int type)
{
	if (!mini->token)
	{
		create_first_node(mini, str, type);
		return ;
	}
	if (type == ARG)
	{
		mini->token->cmd = increase_tab(mini->token->cmd, str);
		return ;
	}
	while (mini->token->next)
		mini->token = mini->token->next;
	mini->token->next = new_token(str, type, mini);
	mini->token = mini->token->next;
}
