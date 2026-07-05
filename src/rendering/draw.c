/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 23:07:40 by ffrattar          #+#    #+#             */
/*   Updated: 2026/07/04 23:08:02 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line(t_xy_point p1, t_xy_point p2, int color, t_img *frame)
{
	t_xy_point	dest;
	t_xy_point	step;
	int			err;
	int			e2;

	init_steps(&dest, &step, &p1, &p2);
	err = dest.x - dest.y;
	while (1)
	{
		pixel_put(frame, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = err * 2;
		if (e2 > -dest.y)
		{
			err -= dest.y;
			p1.x += step.x;
		}
		if (e2 < dest.x)
		{
			err += dest.x;
			p1.y += step.y;
		}
	}
	return ;
}

void	draw_view_line(t_player *player, int color, int range, t_img *frame)
{
	t_xy_point	player_pos;
	t_xy_point	player_dest;
	double		dx;
	double		dy;

	if (player->x < range)
		player_pos.x = (player->x) * MINI_SCALE;
	else
		player_pos.x = (int)((range) * MINI_SCALE);
	if (player->y < range)
		player_pos.y = (player->y) * MINI_SCALE;
	else
		player_pos.y = (int)((range) * MINI_SCALE);
	dx = cos(player->angle) * MINI_SCALE;
	dy = -sin(player->angle) * MINI_SCALE;
	player_dest.x = (player_pos.x + (int)dx);
	player_dest.y = (player_pos.y + (int)dy);
	draw_line(player_pos, player_dest, color, frame);
}

void	draw_fov(t_cub *cub)
{
	int			d;
	int			color;
	t_xy_point	r_point;
	t_xy_point	p_point;

	p_point.x = cub->player.x * MINI_SCALE;
	p_point.y = cub->player.y * MINI_SCALE;
	d = 0;
	while (d < FOV)
	{
		color = FOV_COLOR;
		r_point.x = cub->rays[d].x * MINI_SCALE;
		r_point.y = cub->rays[d].y * MINI_SCALE;
		draw_line(p_point, r_point, color, &(cub->frame));
		d++;
	}
}
