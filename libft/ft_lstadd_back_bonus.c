/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:16:34 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/20 09:16:51 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node_ptr;

	node_ptr = *lst;
	if (!new)
		return ;
	if (node_ptr == NULL)
		*lst = new;
	else
	{
		while (node_ptr->next != NULL)
			node_ptr = node_ptr->next;
		node_ptr->next = new;
	}
}
/* 
int	main(void)
{
	t_list	*one;
	t_list	*two;
	t_list	*new_last;

	new_last = ft_lstnew("This should be last node");
	printf("newlast: %s\n", (char *)(new_last)->content);
	one = ft_lstnew("first node");
	printf("one prima: %s\n", (char *)(one)->content);
	two = ft_lstnew("second node will be first");
	printf("two prima: %s\n", (char *)(two)->content);
	ft_lstadd_front(&one, two);
	printf("primo dopo ordine: %s\n", (char *)(one)->content);
	printf("secondo accesso con next: %s\n", (char *)(one)->next->content);
	ft_lstadd_back(&one, new_last);
	printf("ultimo accesso con next: %s\n", (char *)(one)->next->next->content);
	printf("last accesso da content: %s\n", (char *)(new_last)->content);
} */
