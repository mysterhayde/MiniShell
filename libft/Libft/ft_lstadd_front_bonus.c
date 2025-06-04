/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:21:12 by hdougoud          #+#    #+#             */
/*   Updated: 2025/06/04 12:10:55 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Adds 'new' node to the front of linked list 'lst'.
 * @param lst A pointer to the linked list
 * @param new A pointer to the node to be added to the front of 'lst'
 */
{
	new->next = *lst;
	*lst = new;
}

/*int main(void)
	t_list *low= malloc(sizeof(t_list));
	low->content = "Bonjour";
	low->next = NULL;
	t_list *new= malloc(sizeof(t_list));
	new->content = "test";
	ft_lstadd_front(&low, new);
}

 to add in the function
	t_list *liste;
	liste = *lst;
	
	printf("%s\n", new->content);
	printf("%p\n", new->next);
	printf("%s\n", liste->content);
	printf("%p\n", liste->next);
}*/
