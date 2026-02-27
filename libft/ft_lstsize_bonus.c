/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:01:33 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/19 18:09:27 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current;

	i = 0;
	if (lst == NULL)
		return (0);
	current = lst;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}
/*
int	main(void)
{
	t_list	*new;
	t_list	*lst;

	new = ft_lstnew("First");
	lst = ft_lstnew("Now First");
	ft_lstadd_front(&lst, new);
	printf("%d\n", ft_lstsize(lst));
}*/
