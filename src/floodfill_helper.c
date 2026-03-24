/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 02:08:05 by kel               #+#    #+#             */
/*   Updated: 2026/03/24 02:16:20 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	int	init_t_flood(t_flood *f, t_cub *cub, char **vis)
{
	f->grid = cub->map.grid;
	f->vis = vis;
	f->h = cub->map.height;
	f->w = cub->map.width;
	f->stack = malloc(sizeof(int) * (cub->map.height * cub->map.width));
	if (!f->stack)
		return (E_ALLOC_KO);
	f->top = 0;
	return (OK);
}

static	int	flood_next_cell(t_flood *f, int ni, int nj)
{
	int	idx;

	if (ni < 0 || ni >= f->h || nj < 0 || nj >= f->w)
		return (OK);
	if (f->grid[ni][nj] == '0')
		return (E_MAP_OPEN);
	if (f->grid[ni][nj] == ' ' && f->vis[ni][nj] == 0)
	{
		idx = ni * f->w + nj;
		f->stack[f->top] = idx;
		f->top++;
	}
	return (OK);
}

static	int	pop_check_four_dirs(t_flood *f)
{
	int		i;
	int		j;
	int		idx;

	f->top--;
	idx = f->stack[f->top];
	i = idx / f->w;
	j = idx % f->w;
	if (f->vis[i][j] == 1)
		return (OK);
	f->vis[i][j] = 1;
	if (flood_next_cell(f, i - 1, j) != OK)
		return (free(f->stack), E_MAP_OPEN);
	if (flood_next_cell(f, i + 1, j) != OK)
		return (free(f->stack), E_MAP_OPEN);
	if (flood_next_cell(f, i, j - 1) != OK)
		return (free(f->stack), E_MAP_OPEN);
	if (flood_next_cell(f, i, j + 1) != OK)
		return (free(f->stack), E_MAP_OPEN);
	return (OK);
}

int	floodfill_void(t_cub *cub, int r, int c, char **vis)
{
	t_flood	f;
	int		code;

	if (init_t_flood(&f, cub, vis) != OK)
		return (E_ALLOC_KO);
	f.stack[f.top] = r * f.w + c;
	f.top++;
	while (f.top > 0)
	{
		code = pop_check_four_dirs(&f);
		if (code != OK)
			return (code);
	}
	free(f.stack);
	return (OK);
}
