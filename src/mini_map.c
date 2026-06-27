/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:12:41 by ffrattar          #+#    #+#             */
/*   Updated: 2026/05/17 15:15:31 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mini_map_resize(t_cub *cub, char inc)
{
	if (inc == '+')
		cub->map.map_range += 1;

	else if (inc == '-' && cub->map.map_range > 4)
		cub->map.map_range -= 1;
}
