/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 02:24:54 by kel               #+#    #+#             */
/*   Updated: 2026/07/04 22:20:53 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Default x,y for N, default x for S
int	set_spawn_directions(t_cub *cub)
{
	cub->player.dir_x = 0;
	cub->player.dir_y = -1;
	if (cub->map.spawn_dir == 'N')
		cub->player.angle = (PI / 2);
	else if (cub->map.spawn_dir == 'S')
	{
		cub->player.dir_y = +1;
		cub->player.angle = (1.5 * PI);
	}
	else if (cub->map.spawn_dir == 'E')
	{
		cub->player.dir_x = +1;
		cub->player.dir_y = 0;
		cub->player.angle = 0;
	}
	else if (cub->map.spawn_dir == 'W')
	{
		cub->player.dir_x = -1;
		cub->player.dir_y = 0;
		cub->player.angle = (PI);
	}
	else
		return (E_NO_SPAWN);
	return (OK);
}

int	init_player_spawn(t_cub *cub)
{
	int	code;

	if (!cub || cub->map.spawn_count != 1)
		return (E_INVAL_MAP);
	cub->player.x = cub->map.spawn_x + 0.5;
	cub->player.y = cub->map.spawn_y + 0.5;
	cub->map.map_range = MAP_RANGE;
	code = set_spawn_directions(cub);
	if (code != OK)
		return (code);
	return (OK);
}
