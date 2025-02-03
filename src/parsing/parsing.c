/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/03 17:08:48 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Create a new node
 * @param char *str
 * @param int type
 * @return t_token node
 */
t_token	*new_token(char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		show_error("Malloc token failed");
		exit(EXIT_FAILURE);
	}
	new->str = str;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_last_token(char *str, t_mini *mini, int type)
{	
	if (!mini->token)
	{
		mini->backup = malloc(sizeof(t_token));
		mini->token = new_token(str, type);
		if (!mini->token)
		{
			show_error("Malloc backup failed");
			exit(EXIT_FAILURE);
		}
		mini->backup = mini->token;
		return ;
	}
	while (mini->token->next)
		mini->token = mini->token->next;
	mini->token->next = new_token(str, type);
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
	if (str == NULL)
		return ;
	mini->token = NULL;
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		tab[i] = ft_strtrim(tab[i], " ");
		if (is_operator(tab[i]) == 1)
			add_last_token(tab[i], mini, OP);
		else if (mini->token == NULL || mini->token->type == OP)
			add_last_token(tab[i], mini, CMD);
		else if (mini->token->type == CMD || mini->token->type == ARG)
			add_last_token(tab[i], mini, ARG);
		i++;
	}
		mini->token = mini->backup;


	t_token *count;
	count = malloc(sizeof(t_token));
	count = mini->backup;
	while (count)
	{
		if (count->type == 1)
			printf("Token type		%s\n", "CMD");
		else if (count->type == 2)
			printf("Token type		%s\n", "ARG");
		else if (count->type == 3)
			printf("Token type		%s\n", "OP");
		printf("Token string		%s\n", count->str);
		printf("\n");
		count = count->next;
	}

	// j = 0;
	// while(tab[j])
	// 	printf("%s\n", tab[j++]);
	// pid_t	pid;
	// pid = fork();
	// if (pid == 0)
	// {
	// 	char *tmp = ft_strjoin("/bin/", tab[0]);
	// 	if (execve(tmp, tab, NULL) == -1)
	// 		show_error("execve failed");
	// }
	// else
	// 	waitpid(pid, NULL, 0);
}
