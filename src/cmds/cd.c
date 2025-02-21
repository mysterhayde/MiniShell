/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:03:34 by cbopp             #+#    #+#             */
/*   Updated: 2025/02/21 08:05:08 by cbopp            ###   ########.fr       */
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
	if (!path)
		return (show_err_return("cd", ERR_NODIR, ERR_GENERAL));
	if (access(path, F_OK) == -1)
		return (show_err_return("cd", ERR_NODIR, ERR_GENERAL));
	if (access(path, X_OK) == -1)
		return (show_err_return("cd", ERR_PERMISSION, ERR_GENERAL));
	if (chdir(path) == -1)
		return (show_err_return("cd", strerror(errno), ERR_GENERAL));
	return (0);
}
