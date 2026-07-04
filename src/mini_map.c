/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:12:41 by ffrattar          #+#    #+#             */
/*   Updated: 2026/07/04 16:21:36 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mini_map_resize(t_cub *cub, char inc)
{
	if (inc == '+' && (cub->map.map_range <= cub->map.height
			|| cub->map.map_range <= cub->map.width))
		cub->map.map_range += 1;
	else if (inc == '-' && cub->map.map_range > 4)
		cub->map.map_range -= 1;
}

void	mini_map_toggle(t_cub *cub)
{
	if (cub->show_minimap)
		cub->show_minimap = false;
	else
		cub->show_minimap = true;
}
