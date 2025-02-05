/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/04 16:53:58 by hdougoud         ###   ########.fr       */
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
	mini->token = mini->token->next;
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
	int		op;
	char	**tab;

	i = 0;
	if (str == NULL)
		return ;
	mini->token = NULL;
	tab = split_args(str);
	mini->debug = malloc(sizeof(t_debug));
	mini->debug->cmd = tab;
	while (tab[i])
	{
		op = is_operator(mini, tab[i]);
		if (op == 1)
			add_last_token(tab[i], mini, PIPE);
		else if (op == 2)
			add_last_token(tab[i], mini, RDIT);
		else if (mini->token == NULL || mini->token->type == PIPE
			|| mini->token->type == RDIT)
			add_last_token(tab[i], mini, CMD);
		else if (mini->token->type == CMD || mini->token->type == ARG)
			add_last_token(tab[i], mini, ARG);
		i++;
	}
	mini->token = mini->backup;


	// t_token *count;
	// count = malloc(sizeof(t_token));
	// count = mini->backup;
	// while (count)
	// {
	// 	if (count->type == 1)
	// 		printf("Token type		%s\n", "CMD");
	// 	else if (count->type == 2)
	// 		printf("Token type		%s\n", "ARG");
	// 	else if (count->type == 3)
	// 		printf("Token type		%s\n", "PIPE");
	// 	else if (count->type == 4)
	// 		printf("Token type		%s\n", "REDIRECTION");
	// 	printf("Token string		%s\n", count->str);
	// 	printf("\n");
	// 	count = count->next;
	// }
	
	// int	d = 0;
	// while (mini->debug->cmd[d])
	// {
	// 	printf("%s\n", mini->debug->cmd[d]);
	// 	d++;
	// }

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
