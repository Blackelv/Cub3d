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

// set max dof based on largest dim of map
int	get_dof(t_cub *cub)
{
	int	dof;

	dof = 0;
	if (cub->map.height > cub->map.width)
		dof = cub->map.height;
	else
		dof = cub->map.width;
	return (dof);
}

void	setup_gridcheck(t_xy_double *off, t_xy_point *dof, t_cub *cub)
{
	off->x = 0.0;
	off->y = 0.0;
	dof->y = get_dof(cub);
	dof->x = 0;
}

t_xy_double	look_left_right(t_cub *cub, t_xy_point *dof, t_xy_double *off,
		int d)
{
	t_xy_double	r;
	float		tan_a;

	tan_a = -tan(cub->rays[d].ra);
	if (cos(cub->rays[d].ra) > 0.001) // looking left
	{
		r.x = ((int)cub->player.x + 1.0);
		off->x = 1.0;
		off->y = off->x * tan_a;
	}
	else if (cos(cub->rays[d].ra) < -0.001) // looking right
	{
		r.x = (int)cub->player.x - 0.0001;
		off->x = -1.0;
		off->y = off->x * tan_a;
	}
	else
	{
		r.x = cub->player.x;
		r.y = cub->player.y;
		dof->x = dof->y;
	}
	r.y = cub->player.y + (r.x - cub->player.x) * tan_a;
	return (r);
}

t_xy_double	look_up_down(t_cub *cub, t_xy_point *dof, t_xy_double *off, int d)
{
	t_xy_double	r;
	float		tan_a;

	tan_a = -1.0;
	if (tan(cub->rays[d].ra))
		tan_a = -1.0 / tan(cub->rays[d].ra);
	if (sin(cub->rays[d].ra) > 0.001) // looking up
	{
		r.y = (int)cub->player.y - 0.0001;
		off->y = -1.0;
		off->x = off->y * tan_a;
	}
	else if (sin(cub->rays[d].ra) < -0.001) // looking down
	{
		r.y = (int)cub->player.y + 1.0;
		off->y = 1.0;
		off->x = off->y * tan_a;
	}
	else
	{
		r.y = cub->player.y;
		dof->x = dof->y;
	}
	r.x = cub->player.x + (r.y - cub->player.y) * tan_a;
	return (r);
}
