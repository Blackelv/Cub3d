/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:24:21 by kel               #+#    #+#             */
/*   Updated: 2026/03/24 00:36:37 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	valid_chars(t_cub *cub)
{
	int	col;
	int	row;

	row = 0;
	while (row < cub->map.height)
	{
		col = 0;
		while (col < cub->map.width)
		{
			if (ft_strchr(MAP_CHARS, cub->map.grid[row][col]) == NULL)
				return (E_BAD_CHAR);
			col++;
		}
		row++;
	}
	return (OK);
}

static	int	row_scan_loop(t_cub *cub, int row)
{
	int	col;

	col = 0;
	while (col < cub->map.width)
	{
		if (ft_strchr(SPAWN_CHARS, cub->map.grid[row][col]) != NULL)
		{
			cub->map.spawn_count++;
			if (cub->map.spawn_count > 1)
				return (E_MULTI_SPAWN);
			cub->map.spawn_x = col;
			cub->map.spawn_y = row;
			cub->map.spawn_dir = cub->map.grid[row][col];
			cub->map.grid[row][col] = '0';
		}
		col++;
	}
	return (OK);
}

int	valid_spawns(t_cub *cub)
{
	int	code;
	int	row;

	row = 0;
	cub->map.spawn_count = 0;
	while (row < cub->map.height)
	{
		code = row_scan_loop(cub, row);
		if (code != OK)
			return (code);
		row++;
	}
	if (cub->map.spawn_count == 0)
		return (E_NO_SPAWN);
	return (OK);
}

int	map_is_closed(t_cub *cub)
{
	char	**vis;
	int		code;

	if (cub->map.height <= 0 || cub->map.width <= 0)
		return (E_INVAL_MAP);
	if (check_borders(cub))
		return (E_MAP_OPEN);
	vis = visited_arr(cub->map.height, cub->map.width);
	if (!vis)
		return (E_ALLOC_KO);
	code = flood_borders(cub, vis);
	if (code != OK)
	{
		free_visited_arr(vis, cub->map.height);
		return (code);
	}
	free_visited_arr(vis, cub->map.height);
	return (OK);
}

int	scan_validate_map(t_cub *cub)
{
	int	code;

	if (!cub || !cub->map.grid)
		return (E_INVAL_MAP);
	code = valid_chars(cub);
	if (code != OK)
		return (code);
	code = valid_spawns(cub);
	if (code != OK)
		return (code);
	code = map_is_closed(cub);
	if (code != OK)
		return (code);
	return (OK);
}
