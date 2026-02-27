/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:08:42 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/20 11:33:41 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free (lst);
}
/*
void	del_cont(void *content)
{
	free(content);
	content = NULL;
}

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
	ft_lstdelone(new_last, del_cont);
	printf("ultimo ora vuoto?: %s\n", (char *)(one)->next->content);
	printf("ultimo vuoto?: %s\n", (char *)(two)->content);
} */
