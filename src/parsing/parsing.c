/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayden <hayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/14 22:01:58 by hayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**increase_tab(char **tab, char *str)  //TODO: protect mallocs and check possible leaks
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	printf("i = %d\n", i);
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
	free_tab(tab);
	return (new_tab);
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
	new->cmd[0] = str;
	new->cmd[1] = NULL;
	new->type = type;
	new->next = NULL;
	return (new);
}

/**
 * @brief add a node to the end of the linked list
 * @param char *str
 * @param t_mini *mini
 * @param int type
 */
static void	add_last_token(char *str, t_mini *mini, int type)
{
	if (!mini->token)
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
		return ;
	}
	if (type == ARG)
	{
		mini->token->cmd = increase_tab(mini->token->cmd, str);
		return ;
	}
	mini->token = mini->token->next;
	mini->token->next = new_token(str, type);
	mini->token = mini->token->next;
}

static void	allocate_tokens(char *str, t_mini *mini)
{
	int		op;

	op = is_operator(mini, str);
	if (op == 1)
	{
		add_last_token(str, mini, PIPE);
		mini->is_pipe = TRUE;
		mini->pipe_num++;
	}
	else if (op == 2)
		add_last_token(str, mini, RDIT);
	else if (mini->token == NULL || mini->token->type == PIPE
		|| mini->token->type == RDIT)
		add_last_token(str, mini, CMD);
	else if (mini->token->type == CMD || mini->token->type == ARG)
		add_last_token(str, mini, ARG);
}

static void	print_tokens(t_token *token)			// Debug function
{
	while (token)
	{
		if (token->type == CMD)
		{
			int i = 0;
			while (token->cmd[i])
			{
				printf("%s	", token->cmd[i++]);
				printf(COLOR_YELLOW"TYPE:	CMD\n"COLOR_RESET);
			}
		}
		else if (token->type == PIPE)
		{
			printf("%s	", token->cmd[0]);
			printf(COLOR_RED"TYPE:	PIPE\n"COLOR_RESET);
		}
		else if (token->type == RDIT)
		{
			printf("%s	", token->cmd[0]);
			printf("TYPE:	REDIRECTION\n");
		}
		token = token->next;
	}
}

/**
 * @brief parse entry in different tokens and distribute 
 * 		  them in the right categories.
 * @param char *str
 * @param t_mini *mini
 */
void	parsing(char *str, t_mini *mini)
{
	int		i;
	char	**tab;

	i = 0;
	mini->pipe_num = 0;
	mini->is_pipe = FALSE;
	if (str == NULL)
		return ;
	mini->token = NULL;
	tab = split_args(str);
	while (tab[i])
	{
		allocate_tokens(tab[i], mini);
		i++;
	}
	//free_tab(tab);
	print_tokens(mini->backup); // Debug
	mini->token = mini->backup;
	
}
