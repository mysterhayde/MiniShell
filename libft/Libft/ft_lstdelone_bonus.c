/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:08:24 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:50:59 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Deletes a node in a t_list linked list
 * @param lst The linked list
 * @param del The function that will be used to delete the content of a node.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}

//int main(void)
//{
//	t_list *p1 = NULL;
//	t_list *p2 = NULL;
//	t_list *p3 = NULL;
//	p1 = malloc(sizeof(t_list));
//	p2 = malloc(sizeof(t_list));
//	p3 = malloc(sizeof(t_list));
//	p1->content = "Hello";
//	p1->next = p2;
//	p2->content = " ";
//	p2->next = p3;
//	p3->content = "World";
//	p3->next = NULL;
//
//}
