/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:07:43 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/20 12:44:08 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*current;
	t_list	*newnode;
	void	*fcont;

	newlst = NULL;
	current = lst;
	if (!lst || !f)
		return (NULL);
	while (current != NULL)
	{
		fcont = f(current->content);
		newnode = ft_lstnew(fcont);
		ft_lstadd_back(&newlst, newnode);
		current = current->next;
		if (newnode == NULL)
		{
			ft_lstclear(&newlst, del);
			free(fcont);
			return (NULL);
		}
	}
	return (newlst);
}
/* 
void	*print_list(void *content)
{
	printf("%s\n", (char *)content);
	return (0);
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
	ft_lstmap(list, print_list, free);
} */
