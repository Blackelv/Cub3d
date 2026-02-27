/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:45:54 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/20 12:08:25 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/* 
void	print_list(void *content)
{
	printf("%s\n", (char *)content);
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
	ft_lstiter(list, print_list);
} */
