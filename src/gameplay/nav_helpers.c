/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nav_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:15:24 by ffrattar          #+#    #+#             */
/*   Updated: 2026/07/05 14:15:34 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	unit(double dir, double step, int flip)
{
	double	offset;
	double	buffer;
	int		unit;

	offset = 0.5;
	buffer = (step + offset) * flip;
	unit = (int)floor((dir + buffer));
	return (unit);
}
