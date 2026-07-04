/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 23:09:40 by ffrattar          #+#    #+#             */
/*   Updated: 2026/07/04 23:10:03 by ffrattar         ###   ########.fr       */
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
		dst = frame->addr + offset;
		*(unsigned int *)dst = color;
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

int	get_color_from_texture(t_img texture, int x, int y)
{
	char	*color_address;
	int		offset;

	if (x <= texture.w && y <= texture.h)
	{
		offset = ((y * texture.line_len) + (x * (texture.bpp / 8)));
		color_address = texture.addr + offset;
		return (*(unsigned int *)color_address);
	}
	else
		return (*(unsigned int *)texture.addr);
}

int	get_wall_color(t_cub *cub, int d, float h_percent)
{
	int		x;
	int		y;
	float	x_percent;
	float	y_percent;
	int		dir;

	x_percent = fabs(cub->rays[d].x - (float)(int)cub->rays[d].x);
	y_percent = fabs(cub->rays[d].y - (float)(int)cub->rays[d].y);
	if (cub->rays[d].wall == 'N')
		dir = NORTH;
	else if (cub->rays[d].wall == 'E')
		dir = EAST;
	else if (cub->rays[d].wall == 'S')
		dir = SOUTH;
	else if (cub->rays[d].wall == 'W')
		dir = WEST;
	else
		return (FALLBACK_COLOR);
	if (dir == NORTH || dir == SOUTH)
		x = (int)(cub->assets.img[dir].w * x_percent);
	else
		x = (int)(cub->assets.img[dir].w * y_percent);
	y = (int)(cub->assets.img[dir].h * h_percent);
	return (get_color_from_texture(cub->assets.img[dir], x, y));
}
