/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:21:45 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:25:00 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	lastnode_val(t_s_list *stack)
{
	t_s_list	*tmp;

	tmp = stack;
	if (!stack)
		return (0);
	if (stack->next == NULL)
		return (stack->val);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp->val);
}

t_s_list	*ft_lastnode(t_s_list *stack)
{
	if (stack == NULL)
		return (NULL);
	while (stack->next != NULL)
		stack = stack->next;
	return (stack);
}

void	ft_lstcreat_append(t_s_list **stack_a, int n)
{
	t_s_list	*new_node;
	t_s_list	*last_node;

	if (stack_a == NULL)
		return ;
	new_node = malloc(sizeof(t_s_list));
	if (!new_node)
		return ;
	new_node->val = n;
	new_node->index = 0;
	new_node->next = NULL;
	if (*stack_a == NULL)
		*stack_a = new_node;
	else
	{
		last_node = ft_lastnode(*stack_a);
		last_node->next = new_node;
	}
}

int	ft_listsize(t_s_list *lst)
{
	int			i;
	t_s_list	*current;

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

void	ft_indexing_stack(t_s_list *stack, int size)
{
	t_variables	check;

	while (size > 0)
	{
		check.cur_val = NULL;
		check.value = INT_MIN;
		check.current = stack;
		while (check.current)
		{
			if (check.current->val == INT_MIN && check.current->index == 0)
				check.current->index = 1;
			if (check.current->val > check.value && check.current->index == 0)
			{
				check.value = check.current->val;
				check.cur_val = check.current;
				check.current = stack;
			}
			else
				check.current = check.current->next;
		}
		if (check.cur_val != NULL)
			check.cur_val->index = size;
		size--;
	}
}
