/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:27:47 by kel               #+#    #+#             */
/*   Updated: 2026/03/23 00:34:41 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	simple_error_exit(const char *msg)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	get_next_line(-42);
	exit (EXIT_FAILURE);
}

//maybe use clean_cub3d() here?
// void	clean_error_exit(t_cub *cub, const char *msg)
// {
// 	ft_putstr_fd("Error\n", 1);
// 	ft_putstr_fd((char *)msg, 2);
// 	ft_putstr_fd("\n", 2);
// 	if (cub)
// 		clean_cub3d(cub);
// 	get_next_line(-42);
// 	exit (EXIT_FAILURE);
// }

void	clean_cub3d(t_cub *cub)
{
	int	i;

	if (!cub)
		return ;
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
	if (cub->map.raw)
	{
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
	if (cub->map.grid)
	{
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
	if (cub->mlx && cub->frame.img)
	{
		mlx_destroy_image(cub->mlx, cub->frame.img);
		cub->frame.img = NULL;
	}
	if (cub->mlx && cub->win)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		cub->win = NULL;
	}
	get_next_line(-42);
}
