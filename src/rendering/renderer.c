/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 19:53:26 by ffrattar          #+#    #+#             */
/*   Updated: 2026/07/04 23:09:54 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player(t_img *frame, t_player player, int range, int color)
{
	int	i;
	int	j;
	int	x_pos;
	int	y_pos;

	if (player.x < range)
		x_pos = (int)((player.x) * MINI_SCALE);
	else
		x_pos = (int)((range) * MINI_SCALE);
	if (player.y < range)
		y_pos = (int)((player.y) * MINI_SCALE);
	else
		y_pos = (int)((range) * MINI_SCALE);
	i = -(MINI_SCALE / 4);
	while (i < (MINI_SCALE / 4))
	{
		j = -(MINI_SCALE / 4);
		while (j < (MINI_SCALE / 4))
		{
			if ((i * i) + (j * j) <= ((MINI_SCALE / 4) * (MINI_SCALE / 4)))
				pixel_put(frame, x_pos + j, y_pos + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_cub *cub)
{
	double	range;
	int		x_orig;
	int		y_orig;

	range = cub->map.map_range;
	if ((cub->player.x - range) > 0)
		x_orig = (cub->player.x - range);
	else
		x_orig = 0;
	if ((cub->player.y - range) > 0)
		y_orig = (cub->player.y - range);
	else
		y_orig = 0;
	put_minimap(cub, x_orig, y_orig, range);
}

void	draw_columns(t_cub *cub)
{
	int				d;
	t_raycast		ray;
	int				line_height;
	float			dist;
	struct xy_point	start;

	d = FOV - 1;
	while (d >= 0)
	{
		ray = cub->rays[d];
		dist = ray.dist * 2.6;
		if (dist < 1)
			dist = 1;
		line_height = ((3 * WIN_HEIGHT) / dist);
		start.x = (int)(WIN_WIDTH / FOV)*(FOV - d);
		start.y = (int)((WIN_HEIGHT - line_height) / 2);
		put_columns(cub, line_height, start, d);
		d--;
	}
}

void	draw_ceil_floor(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < (WIN_HEIGHT / 2))
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			pixel_put(&(cub->frame), x, y, cub->assets.ceiling);
			x++;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			pixel_put(&(cub->frame), x, y, cub->assets.floor);
			x++;
		}
		y++;
	}
}

int	render(t_cub *cub)
{
	fps_check_constant(); //  remove when done testing @Kelvin
	if (cub->frame.img)
		mlx_destroy_image(cub->mlx, cub->frame.img);
	cub->frame.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->frame.addr = mlx_get_data_addr(cub->frame.img, &cub->frame.bpp,
			&cub->frame.line_len, &cub->frame.endian);
	generate_raycast(cub);
	draw_ceil_floor(cub);
	draw_columns(cub);
	if (cub->show_minimap)
	{
		draw_minimap(cub);
		draw_player(&cub->frame, cub->player, cub->map.map_range, PLAYER_COLOR);
		draw_view_line(&cub->player, VIEW_COLOR, cub->map.map_range,
			&cub->frame);
		if (cub->map.height <= (cub->map.map_range)
			&& cub->map.width <= (cub->map.map_range))
			draw_fov(cub);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame.img, 0, 0);
	return (0);
}
