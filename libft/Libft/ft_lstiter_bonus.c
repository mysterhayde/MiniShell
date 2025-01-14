/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:56:00 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:55:14 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
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
//	ft__lstiter(p1, *f);
//}