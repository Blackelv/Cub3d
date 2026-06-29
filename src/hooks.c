// L / R arrows look left and right

// WASD key move player relative to view orientation

// ESC quits program cleanly

//[X] must close window and program cleanly

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:22:22 by ffrattar          #+#    #+#             */
/*   Updated: 2025/03/06 18:15:27 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	x_press(t_cub **cub)
{
	clean_cub3d(*cub);
	// free(*cub);
	exit(0);
	return (0);
}

int	key_release(int keycode, t_cub **cub)
{
	if (keycode == 0xff1b) // esc
		x_press(cub);
	// if (keycode == 0x7a)
	// {
	// 	if ((cub)->map->z_s < 1.1)
	// 		(cub)->map->z_s += 0.1;
	// 	mlx_clear_window((cub)->mlx, (cub)->win);
	// }
	// if (keycode == 0x78)
	// {
	// 	if ((cub)->map->z_s > 0.1)
	// 		(cub)->map->z_s -= 0.1;
	// 	mlx_clear_window((cub)->mlx, (cub)->win);
	// }
	return (0);
}

//
// W - 0x77
// A - 0x61
// S - 0x73
// D - 0x64

int	key_press(int keycode, t_cub **cub)
{
	// printf("Key Code: %d!\n", keycode);
	// increment = 1.0 / MINI_SCALE;
	// printf("Imcrement %f ", increment);
	if (keycode == 119) // W
		move_player(cub, 'F');
	if (keycode == 115) // S
		move_player(cub, 'B');
	if (keycode == 97) // A
		move_player(cub, 'L');
	if (keycode == 100) // D
		move_player(cub, 'R');
	if (keycode == 0xff51) // Right
		rotate_player(cub, 'L');
	if (keycode == 0xff53) // Left
		rotate_player(cub, 'R');
	// if (keycode == 0xff52)
	// 	mini_map_resize(*cub, '+');
	// if (keycode == 0xff54)
	// 	mini_map_resize(*cub, '-');
	// mlx_clear_window((*cub)->mlx, (*cub)->win);
	return (0);
}
