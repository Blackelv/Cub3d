/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:48:55 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/19 18:19:17 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr_node;

	ptr_node = lst;
	if (ptr_node == NULL)
		return (NULL);
	while (ptr_node->next != NULL)
		ptr_node = ptr_node->next;
	return (ptr_node);
}

/* int	main(void)
{
	t_list	*new;
	t_list	*lst;
	t_list	*nodo;

	new = ft_lstnew("First");
	lst = ft_lstnew("Now First");
	ft_lstadd_front(&lst, new);
	printf("%d\n", ft_lstsize(lst));
	nodo = ft_lstlast(lst);
	printf("%s\n", (char *)nodo->content);
	printf("%s\n", (char *)new->next->content);
} */
