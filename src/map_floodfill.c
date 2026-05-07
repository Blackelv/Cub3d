/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 00:34:04 by kel               #+#    #+#             */
/*   Updated: 2026/03/24 02:16:54 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	top_bottom_flood(t_cub *cub, char **vis)
{
	int	r;
	int	c;
	int	code;

	c = 0;
	while (c < cub->map.width)
	{
		r = 0;
		if (cub->map.grid[r][c] == ' ' && vis[r][c] == 0)
		{
			code = floodfill_void(cub, r, c, vis);
			if (code != OK)
				return (code);
		}
		r = cub->map.height - 1;
		if (cub->map.grid[r][c] == ' ' && vis[r][c] == 0)
		{
			code = floodfill_void(cub, r, c, vis);
			if (code != OK)
				return (code);
		}
		c++;
	}
	return (OK);
}

int	left_right_flood(t_cub *cub, char **vis)
{
	int	r;
	int	c;
	int	code;

	r = 0;
	while (r < cub->map.height)
	{
		c = 0;
		if (cub->map.grid[r][c] == ' ' && vis[r][c] == 0)
		{
			code = floodfill_void(cub, r, c, vis);
			if (code != OK)
				return (code);
		}
		c = cub->map.width - 1;
		if (cub->map.grid[r][c] == ' ' && vis[r][c] == 0)
		{
			code = floodfill_void(cub, r, c, vis);
			if (code != OK)
				return (code);
		}
		r++;
	}
	return (OK);
}

int	flood_borders(t_cub *cub, char **vis)
{
	int	code;

	if (cub->map.height <= 0 || cub->map.width <= 0 || !vis)
		return (E_INVAL_MAP);
	code = top_bottom_flood(cub, vis);
	if (code != OK)
		return (code);
	code = left_right_flood(cub, vis);
	if (code != OK)
		return (code);
	return (OK);
}
