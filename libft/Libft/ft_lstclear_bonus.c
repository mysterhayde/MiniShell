/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:00:35 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:49:59 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Clears a linked list of t_list type
 * @param lst The t_list linked list
 * @param del The delete function.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*blst;

	while (*lst)
	{
		blst = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = blst;
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
//	ft_lstclear(&p1, del);
//}