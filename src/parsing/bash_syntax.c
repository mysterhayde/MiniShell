/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:28:02 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/25 18:37:48 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*clear_quote(char *str, char quote, int *len)
{
	int		j;
	int		i;
	char	*trimmed;

	i = 0;
	j = 0;
	trimmed = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!trimmed)
		return (NULL);
	while (str[j])
	{
		if (str[j] == quote)
		{
			j++;
			*len = j;
			continue ;
		}
		trimmed[i++] = str[j++];
	}
	trimmed[i] = '\0';
	return (free(str), trimmed);
}

char	**check_bash_syntax(char **split)
{
	int		j;
	int		i;
	char	quote;

	j = 0;
	while (split[j])
	{
		i = 0;
		while (split[j][i])
		{
			if (split[j][i] == '\'' || split[j][i] == '\"')
			{
				quote = split[j][i];
				split[j] = clear_quote(split[j], quote, &i);
				if (split[j] == NULL)
					return (NULL);
				continue ;
			}
			i++;
		}
		j++;
	}
	return (split);
}
