/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:23:09 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:48:42 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Adds 'new' node to the back of linked list 'lst'.
 * @param lst A pointer to the linked list
 * @param new A pointer to the node to be added to the end of 'lst'
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ulst;

	ulst = *lst;
	if (*lst != NULL)
	{
		while ((ulst)->next != NULL)
			ulst = ulst->next;
		ulst->next = new;
	}
	else
		*lst = new;
}

//int main(void)
//{
//	t_list	*p1;
//	t_list	*p2;
//	t_list	*new;
//	p1 = malloc(sizeof(t_list));
//	p2 = malloc(sizeof(t_list));
//	new = malloc(sizeof(t_list));
//	p1->content = "Hello";
//	p1->next = p2;
//	p2->content = "World";
//	p2->next = NULL;
//	new->content = "test";
//	new->next = NULL;
//	ft_lstadd_back(&p1 ,new);
//	printf("%d\n", ft_lstsize(p1));
//}
