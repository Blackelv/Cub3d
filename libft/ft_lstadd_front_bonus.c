/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:42:06 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/19 17:59:13 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	*lst = new;
	new->next = temp;
}
/*
int	main(void)
{
	t_list	*new;
	t_list	*lst;

	lst = ft_lstnew("first node");
	printf("prima di funz: %s\n", (char *)(lst)->content);
	new = ft_lstnew("Second node to be first");
	printf("prossimo nodo: %s\n", (char *)(new)->content);
	ft_lstadd_front(&lst, new);
	printf("new dopo funz: %s\n", (char *)(lst)->content);
	printf("prossimo nodo: %s\n", (char *)(lst)->next->content);
}*/
