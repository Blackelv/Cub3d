/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:27:47 by kel               #+#    #+#             */
/*   Updated: 2026/03/24 03:28:42 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	void	clean_texture_paths(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < T_COUNT)
	{
		if (cub->assets.path[i])
		{
			free(cub->assets.path[i]);
			cub->assets.path[i] = NULL;
		}
		i++;
	}
}

static	void	clean_texture_images(t_cub *cub)
{
	int	i;

	if (!cub->mlx)
		return ;
	i = 0;
	while (i < T_COUNT)
	{
		if (cub->assets.img[i].img)
		{
			mlx_destroy_image(cub->mlx, cub->assets.img[i].img);
			cub->assets.img[i].img = NULL;
		}
		i++;
	}
}

static	void	clean_map_raw(t_cub *cub)
{
	int	i;

	if (!cub->map.raw)
		return ;
	i = 0;
	while (i < cub->map.r_count)
	{
		if (cub->map.raw[i])
		{
			free(cub->map.raw[i]);
			cub->map.raw[i] = NULL;
		}
		i++;
	}
	free(cub->map.raw);
	cub->map.raw = NULL;
}

static	void	clean_map_grid(t_cub *cub)
{
	int	i;

	if (!cub->map.grid)
		return ;
	i = 0;
	while (i < cub->map.height)
	{
		if (cub->map.grid[i])
		{
			free(cub->map.grid[i]);
			cub->map.grid[i] = NULL;
		}
		i++;
	}
	free(cub->map.grid);
	cub->map.grid = NULL;
}

void	clean_cub3d(t_cub *cub)
{
	if (!cub)
		return ;
	clean_texture_paths(cub);
	clean_texture_images(cub);
	clean_map_raw(cub);
	clean_map_grid(cub);
	clean_mlx_ptrs(cub);
	get_next_line(-42);
}
