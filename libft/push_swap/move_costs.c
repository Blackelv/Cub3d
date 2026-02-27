/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_costs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:27:44 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:25:54 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_abs_val(int mov_a, int mov_b)
{
	if (mov_a < 0)
		mov_a *= -1;
	if (mov_b < 0)
		mov_b *= -1;
	if (mov_a > mov_b)
		return (mov_a);
	if (mov_b > mov_a)
		return (mov_b);
	else
		return (mov_a);
}

int	that_small_move(int *costs, int size_b)
{
	int		i;
	int		tmp_move;
	int		the_move;

	i = 0;
	tmp_move = costs[0];
	the_move = 0;
	while (i < size_b && costs)
	{
		if (costs[i] < tmp_move)
		{
			tmp_move = costs[i];
			the_move = i;
		}
		i++;
	}
	free(costs);
	return (the_move);
}

int	*fetch_acosts(int *loc_a, int *loc_b, int size_b)
{
	int	*costs;
	int	i;

	i = 0;
	costs = malloc(sizeof(costs) * size_b);
	while (i < size_b && costs)
	{
		if ((loc_a[i] > 0 && loc_b[i] > 0) || (loc_a[i] < 0 && loc_b[i] < 0))
			costs[i] = ft_abs_val(loc_a[i], loc_b[i]);
		else
		{
			if (loc_a[i] < 0)
				loc_a[i] *= -1;
			if (loc_b[i] < 0)
				loc_b[i] *= -1;
			costs[i] = loc_a[i] + loc_b[i];
		}
		i++;
	}
	return (costs);
}

int	fall_moves(int *move_a, int *move_b, int size_b)
{
	int	i;
	int	the_move;
	int	*costs;
	int	*local_a;
	int	*local_b;

	i = 0;
	local_a = malloc(sizeof(local_a) * size_b);
	local_b = malloc(sizeof(local_b) * size_b);
	if (!local_a || !local_b)
		return (free (local_a), free (local_b), 0);
	while (i < size_b)
	{
		local_a[i] = move_a[i];
		local_b[i] = move_b[i];
		i++;
	}
	costs = fetch_acosts(local_a, local_b, size_b);
	the_move = that_small_move(costs, size_b);
	free (local_a);
	free (local_b);
	return (the_move);
}

int	prepare_a(int move_a, int move_b, t_s_list **s_a, t_s_list **s_b)
{
	while (move_a > 0 && move_b > 0)
	{
		rr(s_a, s_b);
		move_a--;
		move_b--;
	}
	while (move_a < 0 && move_b < 0)
	{
		rrr(s_a, s_b);
		move_a++;
		move_b++;
	}
	if (move_a < 0)
		while (move_a++ < 0)
			rra(s_a);
	else if (move_a > 0)
		while (move_a-- > 0)
			ra(s_a);
	return (move_b);
}
