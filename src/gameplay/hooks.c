/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:22:22 by ffrattar          #+#    #+#             */
/*   Updated: 2026/07/04 22:22:08 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// L / R arrows look left and right
// WASD key move player relative to view orientation
// ESC & [X] quits program cleanly
// [SPACEBAR] toggles minimap
// [+]/[-] keys grow and shrink minimap (FOV visible on max size)

#include "cub3D.h"

int	x_press(t_cub **cub)
{
	clean_cub3d(*cub);
	free(*cub);
	exit(0);
	return (0);
}

int	key_release(int keycode, t_cub **cub)
{
	if (keycode == 0xff1b)
		x_press(cub);
	return (0);
}

int	key_press(int keycode, t_cub **cub)
{
	if (keycode == 119)
		move_player(cub, 'F');
	if (keycode == 115)
		move_player(cub, 'B');
	if (keycode == 97)
		move_player(cub, 'L');
	if (keycode == 100)
		move_player(cub, 'R');
	if (keycode == 0xff51)
		rotate_player(cub, 'L');
	if (keycode == 0xff53)
		rotate_player(cub, 'R');
	if (keycode == 0xff52)
		mini_map_resize(*cub, '+');
	if (keycode == 0xff54)
		mini_map_resize(*cub, '-');
	if (keycode == 0x20)
		mini_map_toggle(*cub);
	return (0);
}
