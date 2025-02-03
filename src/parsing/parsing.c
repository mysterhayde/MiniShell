/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/03 11:02:17 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_cmd(char *str, t_token *token)
{
	if (token == NULL)
	{
		token = malloc(sizeof(t_token))
	}
	token->str = str;
	token->cmd = TRUE;
	token->arg = FALSE;
	token->control_operator = FALSE;
	token->redirection_operator = FALSE;
}

char	*parsing(char *str, t_token *token)
{
	int		i;
	char **tab;

	i = 0;
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		tab[i] = ft_strtrim(tab[i], " ");
		if (token == NULL)
			token_cmd(tab[i], token);
		if (token)
		i++;
	}
	return (str);
}
