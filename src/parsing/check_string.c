/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:07:28 by hdougoud          #+#    #+#             */
/*   Updated: 2025/02/26 11:49:26 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *clear_string(char *str, char **envp)
{
	if (envp)
		return (str);
	return (str);
}

char *check_string(char *str, char **envp)
{
	if (envp)
		return (str);
	return (clear_string);
}