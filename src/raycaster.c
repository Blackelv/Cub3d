/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 07:49:02 by ffrattar          #+#    #+#             */
/*   Updated: 2026/07/02 08:41:45 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	generate_raycast(t_cub *cub)
{
	t_xy_double	p;
	t_xy_double	r;
	int			d;
	float		Tan;
	float		x_off;
	float		y_off;
	int			dof;
	t_xy_double	dist;
	t_xy_point	grid;
	t_xy_double	v;
	t_xy_double	h;
	int			DOF;
	t_raycast	*rays;
	float		wall_val;
	float		angle;

	// t_xy_double	h;
	// t_xy_point	r_point;
	// t_xy_point	p_point;
	rays = cub->raycaster;
	p.x = cub->player.x;
	p.y = cub->player.y;
	// set max DOF based on largest dim of map
	DOF = cub->map.width;
	if (cub->map.height > DOF)
		DOF = cub->map.height;
	d = 0;
	// printf("Wall Vals: ");
	while (d < FOV)
	{
		dof = 0;
		dist.x = 1000000;
		dist.y = 1000000;
		angle = (cub->player.angle) + ((d - (FOV / 2.0)) * DEG_1);
		if (angle < 0)
			rays[d].ra = angle + (2 * PI);
		else if (angle > (2 * PI))
			rays[d].ra = angle - (2 * PI);
		else
			rays[d].ra = angle;
		// ray angle
		//--------------   Vertical Line Check -----------------------
		Tan = -tan(rays[d].ra);
		if (cos(rays[d].ra) > 0.001) // looking left
		{
			r.x = ((int)p.x + 1.0);
			x_off = 1.0;
			y_off = x_off * Tan;
		}
		else if (cos(rays[d].ra) < -0.001) // looking right
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
			if (grid.x >= 0 && grid.x < cub->map.width && grid.y >= 0
				&& grid.y < cub->map.height
				&& cub->map.grid[grid.y][grid.x] == '1')
			{
				dof = DOF; // end loop
				dist.y = cos(rays[d].ra) * (r.x - p.x) - sin(rays[d].ra) * (r.y
						- p.y);
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
		if (tan(rays[d].ra))
			Tan = -1.0 / tan(rays[d].ra);
		else
			Tan = -1.0;
		if (sin(rays[d].ra) > 0.001) // looking up
		{
			r.y = (int)p.y - 0.0001;
			y_off = -1.0;
			x_off = y_off * Tan;
		}
		else if (sin(rays[d].ra) < -0.001) // looking down
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
			if (grid.x >= 0 && grid.x < cub->map.width && grid.y >= 0
				&& grid.y < cub->map.height
				&& cub->map.grid[grid.y][grid.x] == '1')
			{
				dof = DOF; // end loop
				dist.x = cos(rays[d].ra) * (r.x - p.x) - sin(rays[d].ra) * (r.y
						- p.y);
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
		// if y = int, then horiz, if x = int, then vert
		// Identify shortest line
		if (dist.y < dist.x)
		{
			// identify orientation of line
			rays[d].x = v.x;
			rays[d].y = v.y;
			rays[d].dist = dist.y;
		}
		else
		{
			rays[d].x = r.x;
			rays[d].y = r.y;
			rays[d].dist = dist.x;
		}
		// identify wall orientation:
		wall_val = fabs(1.0 - fabs(rays[d].x - (float)(int)rays[d].x));
		if (wall_val >= 0.9999 || wall_val < 0.0001) // vertical
		{
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
		// printf("[%c]: %f,", rays[d].wall, wall_val);
		d++;
	}
	// printf("\n\n");
	return (1);
}

// int	generate_raycast(t_cub *cub)
// {
// 	double		ra;
// 	t_xy_double	p;
// 	t_xy_double	r;
// 	float		Tan;
// 	float		x_off;
// 	float		y_off;
// 	int			dof;
// 	t_xy_double	dist;
// 	t_xy_point	grid;
// 	t_xy_double	v;
// 	t_xy_double	h;
// 	int			DOF;
// 	int			d;

// 	p.x = cub->player.x;
// 	p.y = cub->player.y;
// 	// set max DOF based on largest dim of map
// 	DOF = cub->map.width;
// 	if (cub->map.height > DOF)
// 		DOF = cub->map.height;
// 	d = 0;
// 	while (d < FOV)
// 	{
// 		dof = 0;
// 		dist.x = 1000000;
// 		dist.y = 1000000;
// 		ra = (cub->player.angle) + ((d - (FOV / 2.0)) * DEG_1);
// 		// ray angle
// 		//--------------   Vertical Line Check -----------------------
// 		Tan = -tan(ra);
// 		if (cos(ra) > 0.001) // looking left
// 		{
// 			r.x = ((int)p.x + 1.0);
// 			x_off = 1.0;
// 			y_off = x_off * Tan;
// 		}
// 		else if (cos(ra) < -0.001) // looking right
// 		{
// 			r.x = (int)p.x - 0.0001;
// 			x_off = -1.0;
// 			y_off = x_off * Tan;
// 		}
// 		else
// 		{
// 			r.x = p.x;
// 			r.y = p.y;
// 			dof = DOF;
// 		}
// 		r.y = p.y + (r.x - p.x) * Tan; // initial Y
// 		// check vertical grid lines
// 		while (dof < DOF)
// 		{
// 			grid.x = (int)(r.x);
// 			grid.y = (int)(r.y);
// 			if (grid.x >= 0 && grid.x < cub->map.width && grid.y >= 0
// 				&& grid.y < cub->map.height
// 				&& cub->map.grid[grid.y][grid.x] == '1')
// 			{
// 				dof = DOF; // end loop
// 				dist.y = cos(ra) * (r.x - p.x) - sin(ra) * (r.y - p.y);
// 			}
// 			else
// 			{
// 				// check next gridline
// 				r.x += x_off;
// 				r.y += y_off;
// 				dof += 1;
// 			}
// 		}
// 		// vertical hit
// 		v.x = r.x;
// 		v.y = r.y;
// 		// --------------horzontal line check -----------------------------
// 		dof = 0;
// 		// horizontal line angle
// 		if (tan(ra))
// 			Tan = -1.0 / tan(ra);
// 		else
// 			Tan = -1.0;
// 		if (sin(ra) > 0.001) // looking up
// 		{
// 			r.y = (int)p.y - 0.0001;
// 			y_off = -1.0;
// 			x_off = y_off * Tan;
// 		}
// 		else if (sin(ra) < -0.001) // looking down
// 		{
// 			r.y = (int)p.y + 1.0;
// 			y_off = 1.0;
// 			x_off = y_off * Tan;
// 		}
// 		else
// 		{
// 			r.x = p.x;
// 			r.y = p.y;
// 			dof = DOF;
// 		}
// 		r.x = p.x + (r.y - p.y) * Tan;
// 		// check horzontal grid lines
// 		while (dof < DOF)
// 		{
// 			grid.x = (int)(r.x);
// 			grid.y = (int)(r.y);
// 			if (grid.x >= 0 && grid.x < cub->map.width && grid.y >= 0
// 				&& grid.y < cub->map.height
// 				&& cub->map.grid[grid.y][grid.x] == '1')
// 			{
// 				dof = DOF; // end loop
// 				dist.x = cos(ra) * (r.x - p.x) - sin(ra) * (r.y - p.y);
// 			}
// 			else
// 			{
// 				// check next gridline
// 				r.x += x_off;
// 				r.y += y_off;
// 				dof += 1;
// 			}
// 		}
// 		// horizontal hit
// 		h.x = r.x;
// 		h.y = r.y;
// 		// Identify shortest line
// 		if (dist.y < dist.x)
// 		{
// 			r.x = v.x;
// 			r.y = v.y;
// 			dist.x = dist.y;
// 		}
// 		// saving
// 		cub->raycaster[d].x = r.x;
// 		cub->raycaster[d].y = r.y;
// 		// r_point[d].x = r.x * MINI_SCALE;
// 		// r_point[d].y = r.y * MINI_SCALE;
// 		d++;
// 	}
// 	return (1);
// }
