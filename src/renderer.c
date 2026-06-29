/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 19:53:26 by ffrattar          #+#    #+#             */
/*   Updated: 2026/06/29 20:56:16 by ffrattar         ###   ########.fr       */
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
	double		ra;
	t_xy_double	p;
	t_xy_double	r;
	int			d;
	t_xy_point	r_point;
	t_xy_point	p_point;
	float		Tan;
	float		x_off;
	float		y_off;
	int			dof;
	t_xy_double	dist;
	t_xy_point	grid;
	t_xy_double	v;
	t_xy_double	h;

	p.x = cub->player.x;
	p.y = cub->player.y;
	d = -30;
	while (d < 30)
	{
		dof = 0;
		dist.x = 1000000;
		dist.y = 1000000;
		ra = (cub->player.angle) + (d * DEG_1); // ray angle
		//-----   Vertical Line Check -----------------------
		Tan = -tan(ra);
		if (cos(ra) > 0.001) // looking left
		{
			r.x = ((int)p.x + 1.0);
			x_off = 1.0;
			y_off = x_off * Tan;
		}
		else if (cos(ra) < -0.001) // looking right
		{
			r.x = (int)p.x - 0.0001;
			x_off = -1.0;
			y_off = x_off * Tan;
		}
		else
		{
			r.x = p.x;
			r.y = p.y;
			dof = DOF;
		}
		r.y = p.y + (r.x - p.x) * Tan; // initial Y
		// check vertical grid lines
		while (dof < DOF)
		{
			grid.x = (int)(r.x);
			grid.y = (int)(r.y);
			printf("[V] grid x: %d, grid y : %d\n", grid.x, grid.y);
			if (grid.x >= 0 && grid.x < cub->map.width && grid.y >= 0
				&& grid.y < cub->map.height
				&& cub->map.grid[grid.y][grid.x] == '1')
			{
				dof = DOF; // end loop
				dist.y = cos(ra) * (r.x - p.x) - sin(ra) * (r.y - p.y);
			}
			else
			{
				// check next gridline
				r.x += x_off;
				r.y += y_off;
				dof += 1;
			}
		}
		// vertical hit
		v.x = r.x;
		v.y = r.y;
		// --------------horzontal line check -----------------------------
		dof = 0;
		// horizontal line angle
		if (tan(ra))
			Tan = -1.0 / tan(ra);
		else
			Tan = -1.0;
		if (sin(ra) > 0.001) // looking up
		{
			r.y = (int)p.y - 0.0001;
			y_off = -1.0;
			x_off = y_off * Tan;
		}
		else if (sin(ra) < -0.001) // looking down
		{
			r.y = (int)p.y + 1.0;
			y_off = 1.0;
			x_off = y_off * Tan;
		}
		else
		{
			r.x = p.x;
			r.y = p.y;
			dof = DOF;
		}
		r.x = p.x + (r.y - p.y) * Tan;
		// check horzontal grid lines
		while (dof < DOF)
		{
			grid.x = (int)(r.x);
			grid.y = (int)(r.y);
			printf("[H] grid x: %d, grid y : %d\n", grid.x, grid.y);
			if (grid.x >= 0 && grid.x < cub->map.width && grid.y >= 0
				&& grid.y < cub->map.height
				&& cub->map.grid[grid.y][grid.x] == '1')
			{
				dof = DOF; // end loop
				dist.x = cos(ra) * (r.x - p.x) - sin(ra) * (r.y - p.y);
			}
			else
			{
				// check next gridline
				r.x += x_off;
				r.y += y_off;
				dof += 1;
			}
		}
		// horizontal hit
		h.x = r.x;
		h.y = r.y;
		// Identify shortest line
		if (dist.y < dist.x)
		{
			r.x = v.x;
			r.y = v.y;
			dist.x = dist.y;
		}
		r_point.x = r.x * MINI_SCALE;
		r_point.y = r.y * MINI_SCALE;
		p_point.x = p.x * MINI_SCALE;
		p_point.y = p.y * MINI_SCALE;
		draw_line(p_point, r_point, color, &(cub->frame));
		d++;
	}
	// draw primary view line
	// draw_unit_line(&cub->frame, &cub->player, cub->map.map_range, color);
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
					block_put(&cub->frame, x - x_orig, y - y_orig, 0x00FFFF);
				else if (cub->map.grid[y][x] == '1')
					block_put(&cub->frame, x - x_orig, y - y_orig, 0xFF0000);
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
	draw_view_line(&cub->player, 0xFF0000, &cub->frame);
	draw_fov(cub, 0x000000);
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
