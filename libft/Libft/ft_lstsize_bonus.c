/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:18:52 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:54:35 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Counts the number of nodes in a linked list
 * @param lst A pointer to the linked list.
 * @return The number of nodes in the list.
 */
int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

//int main(void)
//{
//	t_list *p1 = NULL;
//	t_list *p2 = NULL;
//	t_list *p3 = NULL;
//	t_list *p0 = NULL;
//	p1 = malloc(sizeof(t_list));
//	p2 = malloc(sizeof(t_list));
//	p3 = malloc(sizeof(t_list));
//	p0 = malloc(sizeof(t_list));
//	p1->content = "Hello";
//	p1->next = p2;
//	p2->content = " ";
//	p2->next = p3;
//	p3->content = "World";
//	p3->next = NULL;
//	p0->content = "ok";
//	p0->next = p1;
//	printf("%d\n", ft_lstsize(p0));
//}