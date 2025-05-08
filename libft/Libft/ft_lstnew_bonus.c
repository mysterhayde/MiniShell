/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:30:44 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 15:54:05 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Makes a new list with the first node containing the content 'content'
 * @param content The content to be held in the node.
 * @returns A pointer to the node.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

//int main(void)
//{
//	t_list *text;
//
//	text = ft_lstnew("Hello World");
//	printf("%s\n", text->content);
//	printf("%p\n", text->next);
//	return (0);
//}