/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 07:49:02 by ffrattar          #+#    #+#             */
/*   Updated: 2026/07/04 17:17:17 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_vertical_gridlines(t_xy_double *v, t_cub *cub, t_xy_double *dist,
		int d)
{
	t_xy_double	off;
	t_xy_point	grid;
	t_xy_point	dof;

	setup_gridcheck(&off, &dof, cub);
	*v = look_left_right(cub, &dof, &off, d);
	while (dof.x < dof.y)
	{
		grid.x = (int)(v->x);
		grid.y = (int)(v->y);
		if (grid.x >= 0 && grid.x < cub->map.width && grid.y >= 0
			&& grid.y < cub->map.height && cub->map.grid[grid.y][grid.x] == '1')
		{
			dof.x = dof.y; // end loop
			dist->y = cos(cub->rays[d].ra) * (v->x - cub->player.x)
				- sin(cub->rays[d].ra) * (v->y - cub->player.y);
		}
		else
		{
			// check next gridline
			v->x += off.x;
			v->y += off.y;
			dof.x += 1;
		}
	}
}

void	check_horizontal_gridlines(t_xy_double *h, t_cub *cub,
		t_xy_double *dist, int d)
{
	t_xy_double	off;
	t_xy_point	grid;
	t_xy_point	dof;

	setup_gridcheck(&off, &dof, cub);
	*h = look_up_down(cub, &dof, &off, d);
	while (dof.x < dof.y)
	{
		grid.x = (int)(h->x);
		grid.y = (int)(h->y);
		if (grid.x >= 0 && grid.x < cub->map.width && grid.y >= 0
			&& grid.y < cub->map.height && cub->map.grid[grid.y][grid.x] == '1')
		{
			dof.x = dof.y; // end loop
			dist->x = cos(cub->rays[d].ra) * (h->x - cub->player.x)
				- sin(cub->rays[d].ra) * (h->y - cub->player.y);
		}
		else
		{
			h->x += off.x;
			h->y += off.y;
			dof.x += 1;
		}
	}
}

// Identify shortest line
void	id_shortest_raytrace(t_cub *cub, t_xy_double r[2],
		t_xy_double dist, int d)
{
	t_raycast	*rays;

	rays = cub->rays;
	if (dist.y < dist.x)
	{
		// identify orientation of line
		rays[d].x = r[0].x;
		rays[d].y = r[0].y;
		rays[d].dist = dist.y;
	}
	else
	{
		rays[d].x = r[1].x;
		rays[d].y = r[1].y;
		rays[d].dist = dist.x;
	}
}

// apply wall orientation
void	id_wall_orientations(t_raycast *rays, int d)
{
	struct xy_double	w;

	w.x = fabs(1.0 - fabs(rays[d].x - (float)(int)rays[d].x));
	if (d == 0 || (d < (FOV - 1) && (fabs(rays[d].dist - rays[d - 1].dist\
) > fabs(rays[d].dist - rays[d + 1].dist))))
		w.y = fabs(1.0 - fabs(rays[d + 1].x - (float)(int)rays[d + 1].x));
	else
		w.y = fabs(1.0 - fabs(rays[d - 1].x - (float)(int)rays[d - 1].x));
	if ((w.x >= 0.99999 || w.x < 0.001) && (w.y >= 0.99999 || w.y < 0.001))
	{
		// vertical
		if ((rays[d].ra) > (PI / 2) && rays[d].ra < (3 * PI / 2))
		{
			rays[d].wall = 'W';
		}
		else
			rays[d].wall = 'E';
	}
	else // horizontal
	{
		if (rays[d].ra > PI)
			rays[d].wall = 'S';
		else
			rays[d].wall = 'N';
	}
}

void	generate_raycast(t_cub *cub)
{
	t_xy_double	r[2];
	int			d;
	t_xy_double	dist;
	float		angle;

	d = 0;
	while (d < FOV)
	{
		dist.x = 1000000;
		dist.y = 1000000;
		angle = (cub->player.angle) + ((d - (FOV / 2.0)) * DEG_1);
		if (angle < 0)
			cub->rays[d].ra = angle + (2 * PI);
		else if (angle > (2 * PI))
			cub->rays[d].ra = angle - (2 * PI);
		else
			cub->rays[d].ra = angle;
		check_vertical_gridlines(&r[0], cub, &dist, d);
		check_horizontal_gridlines(&r[1], cub, &dist, d);
		id_shortest_raytrace(cub, r, dist, d);
		id_wall_orientations(cub->rays, d);
		d++;
	}
}
