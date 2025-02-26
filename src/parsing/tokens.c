/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:00:12 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/26 15:33:07 by hdougoud         ###   ########.fr       */
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
	if (!mini->backup)
		return ;
	mini->token = mini->backup;
	while (mini->token)
	{
		mini->token = mini->token->next;
		free(mini->backup->cmd);
		free(mini->backup);
		mini->backup = mini->token;
	}
	mini->token = NULL;
	mini->backup = NULL;
}

static char	**increase_tab(char **tab, char *str)  //TODO: protect mallocs and check possible leaks
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
			return (NULL);
		i++;
	}
	new_tab[i] = ft_strdup(str);
	if (!new_tab[i])
		return (NULL);
	new_tab[i + 1] = NULL;
	return (free_tab(tab), new_tab);
}

/**
 * @brief Create a new node
 * @param char *str
 * @param int type
 * @return t_token node
 */
static t_token	*new_token(char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		show_error("Malloc token failed");
		exit(EXIT_FAILURE);
	}
	new->cmd = malloc(sizeof(char *) * 2);
	if (!new->cmd)
	{
		(show_error("Malloc new token failed"));
		return (NULL);
	}
	if (type == LIMITER)
		str = clean_quote(str);
	new->cmd[0] = str;
	new->cmd[1] = NULL;
	new->type = type;
	new->next = NULL;
	return (new);
}

static void	create_first_node(t_mini *mini, char *str, int type)
{
	mini->backup = malloc(sizeof(t_token));
	if (!mini->backup)
	{
		show_error("Malloc backup failed");
		exit(EXIT_FAILURE);
	}
	mini->token = new_token(str, type);
	if (!mini->token)
	{
		show_error("Malloc backup failed");
		exit(EXIT_FAILURE);
	}
	mini->backup = mini->token;
}

/**
 * @brief add a node to the end of the linked list
 * @param char *str
 * @param t_mini *mini
 * @param int type
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
	mini->token->next = new_token(str, type);
	mini->token = mini->token->next;
}