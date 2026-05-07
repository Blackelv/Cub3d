/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:52:55 by kel               #+#    #+#             */
/*   Updated: 2026/03/24 03:27:05 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

const	char	*config_errors(int code)
{
	if (code == E_TEX_PATH_MISSING)
		return (ERR__PATH_M);
	if (code == E_TEX_PATH_TRAILING)
		return (ERR_PATH_T);
	if (code == E_RGB_MISSING)
		return (ERR_RGB_M);
	if (code == E_RGB_FORMAT)
		return (ERR_RGB_F);
	if (code == E_RGB_RANGE)
		return (ERR_RGB_R);
	if (code == E_MISS_NO)
		return (ERR_NO_TEX);
	if (code == E_MISS_SO)
		return (ERR_SO_TEX);
	if (code == E_MISS_WE)
		return (ERR_WE_TEX);
	if (code == E_MISS_EA)
		return (ERR_EA_TEX);
	if (code == E_MISS_TEX)
		return (ERR_MISS_TEX);
	if (code == E_MISS_F)
		return (ERR_F_COLOR);
	if (code == E_MISS_C)
		return (ERR_C_COLOR);
	return (NULL);
}

const	char	*mlx_errors(int code)
{
	if (code == E_MLX_PTR)
		return (ERR_MLX_PTR);
	if (code == E_MLX_IMG)
		return (ERR_MLX_IMG);
	if (code == E_WIN_PTR)
		return (ERR_WIN_PTR);
	if (code == E_IMG_PTR)
		return (ERR_IMG_PTR);
	if (code == E_ADDR_PTR)
		return (ERR_IMG_ADDR);
	if (code == E_TEX_IMG)
		return (ERR_TEX_IMG);
	if (code == E_TEX_ADDR)
		return (ERR_TEX_ADDR);
	return (NULL);
}

const	char	*map_valid_errors(int code)
{
	if (code == E_MISS_COLOR)
		return (ERR_MISS_COLOR);
	if (code == E_BAD_CHAR)
		return (ERR_INVAL_C);
	if (code == E_MULTI_SPAWN)
		return (ERR_MULTI_SPAWN);
	if (code == E_NO_SPAWN)
		return (ERR_NO_SPAWN);
	if (code == E_MAP_OPEN)
		return (ERR_HOLE_MAP);
	return (NULL);
}

const	char	*err_mapper(int code)
{
	const char	*helper;

	helper = parsing_errors(code);
	if (helper != NULL)
		return (helper);
	helper = config_errors(code);
	if (helper != NULL)
		return (helper);
	helper = map_valid_errors(code);
	if (helper != NULL)
		return (helper);
	helper = mlx_errors(code);
	if (helper != NULL)
		return (helper);
	return (GENERIC_ERR);
}

int	err_msg(const char *details, int code)
{
	ft_putstr_fd("Error\n", 2);
	if (details)
	{
		ft_putstr_fd((char *)details, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd((char *)err_mapper(code), 2);
	ft_putstr_fd("\n", 2);
	return (code);
}
