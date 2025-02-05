/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:34 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/05 15:03:35 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Basic cd, not completed
 * @param constchar *path
 * @returns 0 on success, 1 on fail
 * @warning DOES NOT WORK WITH ABSOLUTE PATH
 */
int	cd(const char *path)
{
	if (chdir(path) == 0)
		return (0);
	perror("cd");
	(void)path;
	return (1);
}
