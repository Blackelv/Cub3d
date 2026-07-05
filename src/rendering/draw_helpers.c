/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 23:09:05 by ffrattar          #+#    #+#             */
/*   Updated: 2026/07/04 23:12:04 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	block_put(t_img *frame, int x, int y, int color)
{
	char	*dst;
	int		offset;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (x < 0 || y < 0)
		return ;
	while (i <= MINI_SCALE)
	{
		j = 0;
		while (j < MINI_SCALE)
		{
			offset = (((y * MINI_SCALE) + i) * frame->line_len) + (((x
							* MINI_SCALE) + j) * (frame->bpp / 8));
			dst = frame->addr + offset;
			if (i == 0 || j == 0)
				*(unsigned int *)dst = 0XFFFFFF;
			else
				*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

void	put_minimap(t_cub *cub, int x_orig, int y_orig, int range)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (x < cub->map.width)
		{
			if (((x - cub->player.x) < range) && ((y - cub->player.y) < range))
			{
				if (cub->map.grid[y][x] == '0')
					block_put(&cub->frame, x - x_orig, y - y_orig, BLOCK_COLOR);
				else if (cub->map.grid[y][x] == '1')
					block_put(&cub->frame, x - x_orig, y - y_orig,
						NO_BLOCK_COLOR);
			}
			x++;
		}
		y++;
	}
}

void	put_columns(t_cub *cub, int line_height, struct xy_point start, int d)
{
	int	color;
	int	i;
	int	j;

	i = 0;
	while (i < (int)(WIN_WIDTH / FOV))
	{
		j = 0;
		while (j < line_height)
		{
			color = get_wall_color(cub, d, ((float)j / (float)line_height));
			pixel_put(&(cub->frame), start.x - i, start.y + j, color);
			j++;
		}
		i++;
	}
}
