/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:35:46 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/19 17:52:52 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*root;

	root = malloc(sizeof(t_list));
	if (!root)
		return (NULL);
	root->content = content;
	root->next = NULL;
	return (root);
}
/*
int	main(void)
{
	t_list *new_node;

	new_node = ft_lstnew("abc5");
	printf("%s\n", (char *)new_node->content);
	printf("%s", (char *)new_node->next);
	free(new_node);
}*/
