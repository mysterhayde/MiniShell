/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:33:03 by hdougoud          #+#    #+#             */
/*   Updated: 2024/11/27 10:55:19 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*flst;
	t_list	*bflst;

	bflst = NULL;
	while (lst)
	{
		flst = malloc(sizeof(t_list));
		if (flst == NULL)
		{
			ft_lstclear(&bflst, del);
			return (NULL);
		}
		flst->content = f(lst->content);
		flst->next = NULL;
		ft_lstadd_back(&bflst, flst);
		if (bflst == NULL)
			bflst = flst;
		lst = lst->next;
	}
	return (bflst);
}
