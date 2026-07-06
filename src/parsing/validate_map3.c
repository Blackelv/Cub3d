/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:19:35 by kel               #+#    #+#             */
/*   Updated: 2026/07/06 14:35:06 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	into_the_void(t_cub *cub, int row, int col)
{
	if (row - 1 < 0 || cub->map.grid[row - 1][col] == ' ')
		return (true);
	if (row + 1 >= cub->map.height || cub->map.grid[row + 1][col] == ' ')
		return (true);
	if (col - 1 < 0 || cub->map.grid[row][col - 1] == ' ')
		return (true);
	if (col + 1 >= cub->map.width || cub->map.grid[row][col + 1] == ' ')
		return (true);
	return (false);
}

int	check_within_walls(t_cub *cub)
{
	int	row;
	int	col;

	row = 0;
	while (row < cub->map.height)
	{
		col = 0;
		while (col < cub->map.width)
		{
			if (cub->map.grid[row][col] == '0')
				if (into_the_void(cub, row, col))
					return (E_MAP_OPEN);
			col++;
		}
		row++;
	}
	return (OK);
}
