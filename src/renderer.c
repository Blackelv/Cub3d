/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 19:53:26 by ffrattar          #+#    #+#             */
/*   Updated: 2026/07/04 11:14:31 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	valid_pixel(int x, int y)
{
	if (x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
		return (1);
	return (0);
}

int	pixel_exists(t_img *frame, int x, int y)
{
	char	*dst;
	int		offset;

	if (!valid_pixel(x, y))
		return (0);
	offset = ((y * frame->line_len) + (x * (frame->bpp / 8)));
	dst = frame->addr + offset; // pixel location
	return (*(unsigned int *)dst != 0);
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
		// dst = frame->addr + (y * frame->line_len + x * (frame->bpp / 8));
		// *(unsigned int *)dst = color;
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

int	get_wall_color(char wall)
{
	int	color;

	if (wall == 'N')
		color = 0xEF476F; // red
	else if (wall == 'E')
		color = 0x8338EC; // Blue
	else if (wall == 'S')
		color = 0x06D6A0; // green
	else if (wall == 'W')
		color = 0xC4851F; // green
	else
		color = 0xFFFFFF; // white
	return (color);
}

// Draw FOV
void	draw_fov(t_cub *cub)
{
	int			d;
	int			color;
	t_xy_point	r_point;
	t_xy_point	p_point;
	char		wall;

	p_point.x = cub->player.x * MINI_SCALE;
	p_point.y = cub->player.y * MINI_SCALE;
	d = 0;
	while (d < FOV)
	{
		wall = cub->raycaster[d].wall;
		color = get_wall_color(wall);
		r_point.x = cub->raycaster[d].x * MINI_SCALE;
		r_point.y = cub->raycaster[d].y * MINI_SCALE;
		draw_line(p_point, r_point, color, &(cub->frame));
		d++;
	}
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
			// 						- cub->player.x)) + (fabs(y
			//	- cub->player.y)
			// 					* fabs(y - cub->player.y))))) < range)
			// rectangular preview
			if (((x - cub->player.x) < range) && ((y - cub->player.y) < range))
			{
				if (cub->map.grid[y][x] == '0')
					block_put(&cub->frame, x - x_orig, y - y_orig, 0xD8E2DC);
				else if (cub->map.grid[y][x] == '1')
					block_put(&cub->frame, x - x_orig, y - y_orig, 0xFCA311);
			}
			else
			{
				if (cub->map.grid[y][x] == '0')
					block_put(&cub->frame, x - 6, y - 6, 0x00FFFF);
				else if (cub->map.grid[y][x] == '1')
					block_put(&cub->frame, x - 6, y - 6, 0xFF0000);
			}
			x++;
		}
		y++;
	}
	draw_player(&cub->frame, cub->player, range, 0x000000);
	draw_fov(cub);
	draw_view_line(&cub->player, 0xFF0000, &cub->frame);
	// player_pos.x = cub->player.x;
	// player_pos.y = cub->player.y;
	// draw_line(player_pos, (t_xy_point){0, 0}, 0xFF00FF, &cub->frame);
	// draw_fov(cub, 0xFF00FF);
}

void	draw_columns(t_cub *cub)
{
	int			col_width;
	int			d;
	t_raycast	ray;
	int			line_height;
	float		dist;
	int			start_x;
	int			start_y;
	int			i;
	int			color;
	int			j;

	/// frame dimensions
	col_width = (int)(WIN_WIDTH / FOV);
	// float scale = 0.66
	// ray, distance, direction
	d = FOV - 1;
	while (d >= 0)
	{
		ray = cub->raycaster[d];
		dist = ray.dist * 3;
		if (dist < 1)
			dist = 1;
		line_height = ((3 * WIN_HEIGHT) / dist);
		if (line_height > WIN_HEIGHT)
			line_height = WIN_HEIGHT;
		start_x = col_width * (FOV - d);
		start_y = (int)((WIN_HEIGHT - line_height) / 2);
		i = 0;
		color = get_wall_color(ray.wall);
		while (i < col_width)
		{
			j = 0;
			while (j < line_height)
			{
				// if (!pixel_exists(&(cub->frame), start_x - i, start_y + j))
				pixel_put(&(cub->frame), start_x - i, start_y + j, color);
				j++;
			}
			i++;
		}
		// while (i < line_height)
		// {
		// 	j = 0;
		// 	while (j < col_width)
		// 	{
		// 		if (!pixel_exists(&(cub->frame), start_x - j, start_y + i))
		// 			pixel_put(&(cub->frame), start_x - j, start_y + i, color);
		// 		j++;
		// 	}
		// 	i++;
		// }
		d--;
	}
	// may/min distance
}

void	draw_ceil_floor(t_cub *cub)
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	x = 0;
	ceiling = cub->assets.ceiling;
	floor = cub->assets.floor;
	// ceiling = 0xFFFFFF;
	// floor = 0x666666;
	// printf("Ceiling: %d, Floor: %d\n", ceiling, floor);
	y = 0;
	while (y < (WIN_HEIGHT / 2))
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			// if (!pixel_exists(&(cub->frame), x, y))
			pixel_put(&(cub->frame), x, y, ceiling);
			x++;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			// if (!pixel_exists(&(cub->frame), x, y))
			pixel_put(&(cub->frame), x, y, floor);
			x++;
		}
		y++;
	}
}

int	render(t_cub *cub)
{
	fps_check_constant();
	// clear current img
	if (cub->frame.img)
		mlx_destroy_image(cub->mlx, cub->frame.img);
	cub->frame.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->frame.addr = mlx_get_data_addr(cub->frame.img, &cub->frame.bpp,
			&cub->frame.line_len, &cub->frame.endian);
	generate_raycast(cub);
	// Draw Ceiling/Floor
	draw_ceil_floor(cub);
	// Draw Columns
	draw_columns(cub);
	// Draw Minimap
	draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame.img, 0, 0);
	return (0);
}
