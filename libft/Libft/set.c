/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:43:29 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/08 16:20:04 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Thank you baschnit <3
 * @param void	*target, The variable you want to perform the operation on.
 * @param void	**target_new, The operation you want to perform on target.
 */
void	*set(void *vtarget, void *target_new)
{
	void	**target;

	target = (void **)vtarget;
	*target = target_new;
	return (target_new);
}

/**
 * @brief Same as set() but less lines - Thank you adrian
 * @param void	*target, The variable you want to perform the operation on.
 * @param void	**target_new, The operation you want to perform on target.
 */
void	*set2(void **vtarget, void *target_new)
{
	return (*vtarget = target_new, target_new);
}
