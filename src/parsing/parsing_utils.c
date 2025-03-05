/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:24:41 by hdougoud          #+#    #+#             */
/*   Updated: 2025/03/05 16:57:27 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	skip_until_next_quote(char *str, char quote, int i)
{
	int j;
	int	double_quote;

	j = 0;
	double_quote = 0;
	while (j <= i)
	{
		if (str[j] == '\"')
			double_quote++;
		j++;
	}
	if ((double_quote % 2) != 0)
		return (1);
	return (find_next_quote(str + i, quote));
}

int	find_next_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i + 1);
}

int	is_operator(t_mini *mini, char *str)
{
	if (ft_strmincmp(str, "|", 1) == 0)
	{
		mini->is_pipe = TRUE;
		return (PIPE);
	}
	else if (ft_strmincmp(str, "<", 1) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, ">", 1) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, ">>", 2) == 0)
		return (RDIT);
	else if (ft_strmincmp(str, "<<", 2) == 0)
		return (HERE_DOC);
	else if ((ft_strmincmp(str, "&&", 2) == 0))
		return (AND_OP);
	else if ((ft_strmincmp(str, "||", 2) == 0))
		return (OR_OP);
	return (0);
}
