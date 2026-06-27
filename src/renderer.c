/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 19:53:26 by ffrattar          #+#    #+#             */
/*   Updated: 2026/06/27 18:07:11 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	valid_pixel(int x, int y)
{
	if (x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
		return (1);
	return (0);
}

void	pixel_put(t_img *frame, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (valid_pixel(x, y))
	{
		offset = ((y * frame->line_len) + (x * (frame->bpp / 8)));
		dst = frame->addr + offset; // pixel location
		*(unsigned int *)dst = color;
	}
}

void	block_put(t_img *frame, int x, int y, int color)
{
	char	*dst;
	int		offset;
	int		i;
	int		j;

	int S = MINI_SCALE; // scale factor
	i = 0;
	j = 0;
	if (x < 0 || y < 0)
		return ;
	while (i <= S)
	{
		j = 0;
		while (j < S)
		{
			offset = (((y * S) + i) * frame->line_len) + (((x * S) + j)
					* (frame->bpp / 8));
			dst = frame->addr + offset; // pixel location
			if (i == 0 || j == 0)
				*(unsigned int *)dst = 0XFFFFFF;
			else
				*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

void	init_steps(t_xy_point *dest, t_xy_point *step, t_xy_point *p1,
		t_xy_point *p2)
{
	dest->x = abs(p2->x - p1->x);
	dest->y = abs(p2->y - p1->y);
	if (p1->x < p2->x)
		step->x = 1;
	else
		step->x = -1;
	if (p1->y < p2->y)
		step->y = 1;
	else
		step->y = -1;
}

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

void	draw_view_line(t_player *player, int color, t_img *frame)
{
	t_xy_point	player_pos;
	t_xy_point	player_dest;
	double		dx;
	double		dy;

	player_pos.x = (player->x) * MINI_SCALE;
	player_pos.y = (player->y) * MINI_SCALE;
	dx = cos(player->angle) * MINI_SCALE;
	dy = -sin(player->angle) * MINI_SCALE;
	player_dest.x = (player_pos.x + (int)dx);
	player_dest.y = (player_pos.y + (int)dy);
	// printf("pos: (%d,%d) -> dest (%d,%d)", player_pos.x, player_pos.y,
	// player_dest.x, player_dest.y);
	draw_line(player_pos, player_dest, color, frame);
}

// interpolate and draw single line
void	draw_unit_line(t_img *frame, t_player *player, int range, int color)
{
	int		x;
	int		y;
	int		length;
	double	dx;
	double	dy;
	double	m;

	// int		start[2];
	// range = 8;
	// // set start position
	// if (player.x >= range)
	// 	x_pos = range + (player.x - (int)player.x);
	// else
	// 	x_pos = player.x;
	// if (player.y >= range)
	// 	y_pos = range + (player.y - (int)player.y);
	// else
	// 	y_pos = player.y;
	// start[0] = (player->x) *length = MINI_SCALE;
	// at true map scale
	if (range)
	{
		;
	}
	length = MINI_SCALE;
	dx = cos(player->angle);
	dy = sin(player->angle);
	m = dy / dx;
	x = 0;
	// y = -(MINI_SCALE);
	y = 0;
	while (y < length)
	{
		x = -(MINI_SCALE);
		while (x < length)
		{
			if ((int)(m * x) == (int)(y))
				pixel_put(frame, ((MINI_SCALE + 1) * (player->x) + x),
					(MINI_SCALE * (player->y) + y), color);
			x++;
		}
		y++;
	}
}

// Draw FOV
void	draw_fov(t_cub *cub, int color)

{
	// draw primary view line
	draw_unit_line(&cub->frame, &cub->player, cub->map.map_range, color);
}

// Draw Player
void	draw_player(t_img *frame, t_player player, int range, int color)
{
	int	i;
	int	j;
	int	r;
	int	x_pos;
	int	y_pos;

	r = MINI_SCALE / 4;
	x_pos = (int)(player.x * MINI_SCALE);
	y_pos = (int)(player.y * MINI_SCALE);
	(void)range;
	i = -r;
	while (i < r)
	{
		j = -r;
		while (j < r)
		{
			if ((i * i) + (j * j) <= (r * r))
				pixel_put(frame, x_pos + j, y_pos + i, color);
			j++;
		}
		i++;
	}
	// 	int		i;
	// 	int		j;
	// 	double	r;
	// 	double	x_pos;
	// 	double	y_pos;
	// 	r = round(MINI_SCALE / 3);
	// 	// double	ic;
	// 	// double	jc;
	// 	x_pos = (int)(player.x * MINI_SCALE);
	// 	y_pos = (int)(player.y * MINI_SCALE);
	// 	// (void)range;
	// 	// pixel_put(frame, (player.x * MINI_SCALE), (player.y * MINI_SCALE),
	// 	// color);
	// 	i = -r;
	// 	while (i < r)
	// 	{
	// 		j = -r;
	// 		while (j < r)
	// 		{
	// 			if (fabs(sqrt((i * i) + (j * j))) <= r)
	// 			{
	// 				if (player.x >= range)
	// 					x_pos = range + (player.x - (int)player.x);
	// 				else
	// 					x_pos = player.x;
	// 				if (player.y >= range)
	// 					y_pos = range + (player.y - (int)player.y);
	// 				else
	// 					y_pos = player.y;
	// 				pixel_put(frame, ((int)(x_pos * MINI_SCALE) + j
	//	+ (MINI_SCALE
	// 							/ 2)), ((int)(y_pos * MINI_SCALE) + i
	//			- (MINI_SCALE
	// 							/ 2)), color);
	// 			}
	// 			j++;
	// 		}
	// 		i++;
	// 	}
}

// minimap
void	draw_minimap(t_cub *cub)
{
	int		x;
	int		y;
	double	range;
	int		x_orig;
	int		y_orig;

	// t_xy_point	player_pos;
	// Optionally modify map range
	// cub->map.map_range = 50; // turn into player/map variable?
	range = cub->map.map_range;
	x = 0;
	y = 0;
	if ((cub->player.x - range) > 0)
		x_orig = (cub->player.x - range);
	else
		x_orig = 0;
	if ((cub->player.y - range) > 0)
		y_orig = (cub->player.y - range);
	else
		y_orig = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (x < cub->map.width)
		{
			// circular preview
			// if (ceil(fabs(sqrt((fabs(x - cub->player.x) * fabs(x
			// 						- cub->player.x)) + (fabs(y - cub->player.y)
			// 					* fabs(y - cub->player.y))))) < range)
			// rectangular preview
			if (((x - cub->player.x) < range) && ((y - cub->player.y) < range))
			{
				if (cub->map.grid[y][x] == '0')
					block_put(&cub->frame, x - x_orig, y - y_orig, 0x00FFFF);
				else if (cub->map.grid[y][x] == '1')
					block_put(&cub->frame, x - x_orig, y - y_orig, 0xFF0000);
			}
			// else
			// {
			// 	if (cub->map.grid[y][x] == '0')
			// 		block_put(&cub->frame, x - 6, y - 6, 0x00FFFF);
			// 	else if (cub->map.grid[y][x] == '1')
			// 		block_put(&cub->frame, x - 6, y - 6, 0xFF0000);
			// }
			x++;
		}
		y++;
	}
	draw_player(&cub->frame, cub->player, range, 0x000000);
	draw_view_line(&cub->player, 0xFF0000, &cub->frame);
	// player_pos.x = cub->player.x;
	// player_pos.y = cub->player.y;
	// draw_line(player_pos, (t_xy_point){0, 0}, 0xFF00FF, &cub->frame);
	// draw_fov(cub, 0xFF00FF);
}

// draw borders of map (maybe show only a portion from player)
// draw walls
// draw player position
// add orientation

int	render(t_cub *cub)
{
	// clear current img
	if (cub->frame.img)
		mlx_destroy_image(cub->mlx, cub->frame.img);
	cub->frame.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->frame.addr = mlx_get_data_addr(cub->frame.img, &cub->frame.bpp,
			&cub->frame.line_len, &cub->frame.endian);
	// Draw Minimap
	draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame.img, 0, 0);
	return (0);
}
