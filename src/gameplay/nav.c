/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nav.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 11:23:58 by ffrattar          #+#    #+#             */
/*   Updated: 2026/07/10 20:03:35 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	collision_check(t_cub *cub, char dir, double step)
{
	int	x;
	int	y;

	x = (int)((cub->player.x));
	y = (int)((cub->player.y));
	if (dir == 'N')
		if (cub->map.grid[unit(cub->player.y, step, -1)][x] == '1')
			return (1);
	if (dir == 'S')
		if (cub->map.grid[unit(cub->player.y, -step, 1)][x] == '1')
			return (1);
	if (dir == 'E')
		if (cub->map.grid[y][unit(cub->player.x, step, 1)] == '1')
			return (1);
	if (dir == 'W')
		if (cub->map.grid[y][unit(cub->player.x, step, -1)] == '1')
			return (1);
	return (0);
}

void	update_collisions(t_cub *cub)
{
	double	step;

	step = ((SPEED * 1.0) / MINI_SCALE * 1.0);
	cub->player.collision.n = collision_check(cub, 'N', step);
	cub->player.collision.s = collision_check(cub, 'S', step);
	cub->player.collision.e = collision_check(cub, 'E', step);
	cub->player.collision.w = collision_check(cub, 'W', step);
}

struct xy_double	get_dx_dy(t_cub **cub, char dir)
{
	struct xy_double	d;

	d.x = 0.0;
	d.y = 0.0;
	if (dir == 'F')
	{
		d.x = cos((*cub)->player.angle);
		d.y = -sin((*cub)->player.angle);
	}
	else if (dir == 'B')
	{
		d.x = -cos((*cub)->player.angle);
		d.y = sin((*cub)->player.angle);
	}
	else if (dir == 'L')
	{
		d.x = cos(((*cub)->player.angle) + PI / 2.0);
		d.y = -sin(((*cub)->player.angle) + PI / 2.0);
	}
	else if (dir == 'R')
	{
		d.x = -cos(((*cub)->player.angle) + PI / 2.0);
		d.y = sin(((*cub)->player.angle) + PI / 2.0);
	}
	return (d);
}

void	move_player(t_cub **cub, char dir)
{
	double				step;
	struct xy_double	d;

	d = get_dx_dy(cub, dir);
	step = ((SPEED * 1.0) / MINI_SCALE * 1.0);
	if (fabs(d.x) < 0.001)
		d.x = 0.0;
	if (fabs(d.y) < 0.0001)
		d.y = 0.0;
	update_collisions(*cub);
	if (d.y < 0 && !((*cub)->player.collision.n))
		(*cub)->player.y = (*cub)->player.y + step * d.y;
	if (d.y > 0 && !((*cub)->player.collision.s))
		(*cub)->player.y = (*cub)->player.y + step * d.y;
	if (d.x > 0 && !((*cub)->player.collision.e))
		(*cub)->player.x = (*cub)->player.x + step * d.x;
	if (d.x < 0 && !((*cub)->player.collision.w))
		(*cub)->player.x = (*cub)->player.x + step * d.x;
}

void	rotate_player(t_cub **cub, char dir)
{
	double	new_angle;
	int		r;

	if (dir == 'R')
		r = -1;
	else
		r = 1;
	new_angle = (*cub)->player.angle + ROT * r;
	if (new_angle > 2 * PI)
		new_angle -= 2 * PI;
	else if (new_angle < 0)
		new_angle += 2 * PI;
	(*cub)->player.angle = new_angle;
}
