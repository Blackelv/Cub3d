/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 02:24:54 by kel               #+#    #+#             */
/*   Updated: 2026/06/27 17:26:57 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	set_spawn_directions(t_cub *cub)
{
	if (cub->map.spawn_dir == 'N')
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = -1;
		cub->player.angle = (PI / 2);
	}
	else if (cub->map.spawn_dir == 'S')
	{
		cub->player.dir_x = 0;
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
	code = set_spawn_directions(cub);
	if (code != OK)
		return (code);
	// cub->player.plane_x = -cub->player.dir_y * 0.66;
	// cub->player.plane_y = cub->player.dir_x * 0.66;
	return (OK);
}
