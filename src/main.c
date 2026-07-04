/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:49:28 by kel               #+#    #+#             */
/*   Updated: 2026/07/04 21:06:12 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char *av[])
{
	t_cub	*cub;

	if (ac != 2)
		simple_error_exit(ERR_ARGS);
	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		simple_error_exit(ERR_MALLOC);
	if (parse_n_init_map(cub, av[1]))
	{
		clean_cub3d(cub);
		free(cub);
		exit(EXIT_FAILURE);
	}
	mlx_hook(cub->win, DestroyNotify, 0L, x_press, &cub);
	mlx_hook(cub->win, KeyRelease, 1L << 1, key_release, &cub);
	mlx_hook(cub->win, KeyPress, 1L << 0, key_press, &cub);
	mlx_loop_hook(cub->mlx, render, cub);
	mlx_loop(cub->mlx);
	clean_cub3d(cub);
	free(cub);
	return (0);
}
