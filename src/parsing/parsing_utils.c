/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:24:41 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/16 14:53:11 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_operator(t_mini *mini, char *str)
{
	if (ft_strmincmp(str, "|", 1) == 0)
	{
		mini->is_pipe = TRUE;
		return (1);
	}
	else if (ft_strmincmp(str, "<", 2) == 0)
		return (2);
	else if (ft_strmincmp(str, ">", 2) == 0)
		return (2);
	else if (ft_strmincmp(str, ">>", 1) == 0)
		return (2);
	else if (ft_strmincmp(str, "<<", 1) == 0)
		return (3);
	return (0);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

int	is_printable(char c)
{
	if (c == '!' || c == '$' || c == '\"' || c == '\'')
		return (1);
	else
		return (0);
}
