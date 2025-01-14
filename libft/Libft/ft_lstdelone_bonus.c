/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:08:24 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:55:11 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
