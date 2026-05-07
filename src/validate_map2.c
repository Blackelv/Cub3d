/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:57:10 by kel               #+#    #+#             */
/*   Updated: 2026/03/24 00:29:22 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_visited_arr(char **vis, int n)
{
	int	i;

	if (!vis)
		return ;
	i = 0;
	while (i < n)
	{
		free(vis[i]);
		i++;
	}
	free(vis);
}

char	**visited_arr(int h, int w)
{
	char	**vis;
	int		i;

	vis = ft_calloc(h, sizeof(char *));
	if (!vis)
		return (NULL);
	i = 0;
	while (i < h)
	{
		vis[i] = ft_calloc(w, sizeof(char));
		if (!vis[i])
		{
			while (i-- > 0)
				free(vis[i]);
			free(vis);
			return (NULL);
		}
		i++;
	}
	return (vis);
}

int	check_top_bottom_rows(t_cub *cub)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (col < cub->map.width)
	{
		if (cub->map.grid[row][col] != '1' && cub->map.grid[row][col] != ' ')
			return (E_MAP_OPEN);
		col++;
	}
	row = cub->map.height - 1;
	col = 0;
	while (col < cub->map.width)
	{
		if (cub->map.grid[row][col] != '1' && cub->map.grid[row][col] != ' ')
			return (E_MAP_OPEN);
		col++;
	}
	return (OK);
}

int	check_left_right_cols(t_cub *cub)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (row < cub->map.height)
	{
		if (cub->map.grid[row][col] != '1' && cub->map.grid[row][col] != ' ')
			return (E_MAP_OPEN);
		row++;
	}
	col = cub->map.width - 1;
	row = 0;
	while (row < cub->map.height)
	{
		if (cub->map.grid[row][col] != '1' && cub->map.grid[row][col] != ' ')
			return (E_MAP_OPEN);
		row++;
	}
	return (OK);
}

int	check_borders(t_cub *cub)
{
	int	code;

	code = check_top_bottom_rows(cub);
	if (code != OK)
		return (code);
	code = check_left_right_cols(cub);
	if (code != OK)
		return (code);
	return (OK);
}
