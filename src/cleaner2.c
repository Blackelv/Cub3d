/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:29:13 by kel               #+#    #+#             */
/*   Updated: 2026/05/07 10:03:07 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	simple_error_exit(const char *msg)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	get_next_line(-42);
	exit(EXIT_FAILURE);
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
	if (cub->mlx)
		mlx_destroy_display(cub->mlx);
	if (cub->mlx)
		free(cub->mlx);
}
