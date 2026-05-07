/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:29:13 by kel               #+#    #+#             */
/*   Updated: 2026/03/24 01:30:43 by kel              ###   ########.fr       */
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

void	clean_mlx_ptrs(t_cub *cub)
{
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
}
