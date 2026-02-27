/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:18:57 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/20 11:55:02 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*adjacent;

	if (lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		adjacent = current->next;
		del(current->content);
		free(current);
		current = adjacent;
	}
	*lst = NULL;
}
/* 
void	del_cont(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*list;
	t_list	*one;
	t_list	*two;
	t_list	*new_last;

	list = NULL;
	new_last = ft_lstnew("This should be last node");
	printf("newlast: %s\n", (char *)(new_last)->content);
	one = ft_lstnew("first node will be second");
	printf("one prima: %s\n", (char *)(one)->content);
	two = ft_lstnew("second node will be first");
	printf("two prima: %s\n", (char *)(two)->content);
	ft_lstadd_front(&list, one);
	ft_lstadd_front(&list, two);
	printf("primo dopo ordine: %s\n", (char *)(list)->content);
	printf("secondo accesso con next: %s\n", (char *)(list)->next->content);
	ft_lstadd_back(&list, new_last);
	printf("ultimo accesso da next: %s\n", (char *)(list)->next->next->content);
	printf("last accesso da content: %s\n", (char *)(new_last)->content);
	ft_lstclear(&one, del_cont);
	printf("ultimo vuoto?: %s\n", (char *)(new_last)->content);
} */
