/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nav.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 11:23:58 by ffrattar          #+#    #+#             */
/*   Updated: 2026/06/27 18:43:10 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// calculate grid unit based on scale and step
int	unit(double dir, double step, int pos)
{
	double	buffer;

	buffer = 0.0;
	// if (MINI_SCALE > 10)
	// 	buffer = (1.0 / (MINI_SCALE)) * 3 * pos;
	buffer += step * pos;
	// need to stay 3 steps from wall on large maps
	int unit = (int)floor((dir + buffer)); // round up
	return (unit);
}

// can't get closer than half-way to a wall (based on scale)
int	collision_check(t_cub *cub, char dir, double step)
{
	int	x;
	int	y;

	// check if walls are within collision range
	x = (int)((cub->player.x));
	y = (int)((cub->player.y));
	// printf("Initial x, y: %d, %d\n", x, y);
	if (dir == 'N')
		if (cub->map.grid[unit(cub->player.y, step, -1)][x] == '1')
			return (printf("Hit N Wall!\n"), 1);
	if (dir == 'S')
		if (cub->map.grid[unit(cub->player.y, step, 1)][x] == '1')
			return (printf("Hit S Wall!\n"), 1);
	if (dir == 'E')
		if (cub->map.grid[y][unit(cub->player.x, step, 1)] == '1')
			return (printf("Hit E Wall!\n"), 1);
	if (dir == 'W')
		if (cub->map.grid[y][unit(cub->player.x, step, -1)] == '1')
			return (printf("Hit W Wall!\n"), 1);
	return (0);
}

void	update_collisions(t_cub *cub)
{
	double	step;

	int speed = 1; // maybe convert into player property
	step = ((SPEED * speed * 1.0) / MINI_SCALE * 1.0);
	// printf("Step: %f\n", step);
	cub->player.collision.N = collision_check(cub, 'N', step);
	cub->player.collision.S = collision_check(cub, 'S', step);
	cub->player.collision.E = collision_check(cub, 'E', step);
	cub->player.collision.W = collision_check(cub, 'W', step);
}
// void	move_player(t_cub **cub, char dir)
// {
// 	double	step;

// 	// collision check
// 	update_collisions(*cub);
// 	int speed = 1; // maybe convert into player property
// 	step = ((SPEED * speed * 1.0) / MINI_SCALE * 1.0);
// 	// printf("Step: %f\n", step);
// 	printf("Start: x %f, y %f , ", (*cub)->player.x, (*cub)->player.y);
// 	if (dir == 'N' && !((*cub)->player.collision.N))
// 		(*cub)->player.y = (*cub)->player.y - step;
// 	if (dir == 'S' && !((*cub)->player.collision.S))
// 		(*cub)->player.y = (*cub)->player.y + step;
// 	if (dir == 'E' && !((*cub)->player.collision.E))
// 		(*cub)->player.x = (*cub)->player.x + step;
// 	if (dir == 'W' && !((*cub)->player.collision.W))
// 		(*cub)->player.x = (*cub)->player.x - step;
// 	printf("Stop: x %f, y %f\n", (*cub)->player.x, (*cub)->player.y);
// }

void	move_player(t_cub **cub, char dir)
{
	double	step;
	double	dx;
	double	dy;

	// Calculate dest
	int speed = 1; // maybe convert into player property
	step = ((SPEED * speed * 1.0) / MINI_SCALE * 1.0);
	if (dir == 'F')
	{
		dx = cos((*cub)->player.angle);
		dy = -sin((*cub)->player.angle);
	}
	if (dir == 'B')
	{
		dx = -cos((*cub)->player.angle);
		dy = sin((*cub)->player.angle);
	}
	if (dir == 'L')
	{
		dx = cos(((*cub)->player.angle) + PI / 2);
		dy = -sin(((*cub)->player.angle) + PI / 2);
	}
	if (dir == 'R')
	{
		dx = -cos(((*cub)->player.angle) + PI / 2);
		dy = sin(((*cub)->player.angle) + PI / 2);
	}
	// collision check
	update_collisions(*cub);
	// printf("Step: %f\n", step);
	printf("Start: x %f, y %f , ", (*cub)->player.x, (*cub)->player.y);
	// Apply movement (check for collisions)
	if (dy < 0 && !((*cub)->player.collision.N))
		(*cub)->player.y = (*cub)->player.y + step * dy;
	if (dy > 0 && !((*cub)->player.collision.S))
		(*cub)->player.y = (*cub)->player.y + step * dy;
	if (dx > 0 && !((*cub)->player.collision.E))
		(*cub)->player.x = (*cub)->player.x + step * dx;
	if (dx < 0 && !((*cub)->player.collision.W))
		(*cub)->player.x = (*cub)->player.x + step * dx;
	printf("Stop: x %f, y %f\n", (*cub)->player.x, (*cub)->player.y);
}

void	rotate_player(t_cub **cub, char dir)
{
	int		r;
	double	new_angle;
	double	old_x;
	double	old_y;
	double	l;

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
	printf("Turn %c: %f\n", dir, (*cub)->player.angle);
	// update player vector
	old_x = (*cub)->player.dir_x;
	old_y = (*cub)->player.dir_y;
	(*cub)->player.dir_x = old_x * cos(new_angle) - old_y * sin(new_angle);
	(*cub)->player.dir_y = old_x * sin(new_angle) + old_y * cos(new_angle);
	// normalize to unit length
	l = sqrt((*cub)->player.dir_x * (*cub)->player.dir_x + (*cub)->player.dir_y
			* (*cub)->player.dir_y);
	if (l != 0)
	{
		(*cub)->player.dir_x /= l;
		(*cub)->player.dir_y /= l;
	}
}
