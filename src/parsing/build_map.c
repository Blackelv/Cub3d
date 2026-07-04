/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:32:03 by kel               #+#    #+#             */
/*   Updated: 2026/03/24 16:55:22 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	void	cleanup_grid(t_cub *cub, int i)
{
	while (i-- > 0)
		free(cub->map.grid[i]);
	free(cub->map.grid);
	cub->map.grid = NULL;
}

static	int	alloc_process_row(t_cub *cub, int i)
{
	int	len;

	cub->map.grid[i] = malloc(cub->map.width + 1);
	if (!cub->map.grid[i])
		return (E_ALLOC_KO);
	len = ft_strlen(cub->map.raw[i]);
	ft_strlcpy(cub->map.grid[i], cub->map.raw[i], cub->map.width + 1);
	while (len < cub->map.width)
	{
		cub->map.grid[i][len] = ' ';
		len++;
	}
	cub->map.grid[i][cub->map.width] = '\0';
	return (OK);
}

int	build_map_grid(t_cub *cub)
{
	int	i;
	int	code;

	if (!cub || !cub->map.raw || cub->map.r_count == 0 || cub->map.width <= 0)
		return (E_INVAL_MAP);
	cub->map.grid = malloc(sizeof(*cub->map.grid) * (cub->map.r_count + 1));
	if (!cub->map.grid)
		return (E_ALLOC_KO);
	i = 0;
	while (i < cub->map.r_count)
	{
		code = alloc_process_row(cub, i);
		if (code != OK)
		{
			cleanup_grid(cub, i);
			return (E_ALLOC_KO);
		}
		i++;
	}
	cub->map.grid[i] = NULL;
	cub->map.height = cub->map.r_count;
	cub->map.parsed = true;
	return (OK);
}
