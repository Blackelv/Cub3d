/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:52:55 by kel               #+#    #+#             */
/*   Updated: 2026/03/23 00:25:20 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

const char	*error_helper(int code)
{
	if (code == E_ALLOC_KO)
		return (ERR_MALLOC);
	if (code == E_NAME_KO)
		return (ERR_CUB_FILE);
	if (code == E_OPEN_KO)
		return (ERR_OPEN_FILE);
	if (code == E_IS_DIR)
		return (ERR_DIR);
	if (code == E_XPM_FILE)
		return (ERR_XPM_FILE);
	if (code == E_PRE_MAP)
		return (ERR_PRE_MAP);
	if (code == E_IN_MAP)
		return (ERR_IN_MAP);
	if (code == E_AFTER_MAP)
		return (ERR_MAP_LAST);
	if (code == E_INVAL_MAP)
		return (ERR_INVALID_MAP);
	if (code == E_NO_MAP)
		return (ERR_MISS_MAP);
	if (code == E_SCENE_KO)
		return (ERR_SCENERY);
	if (code == E_DUP_KO)
		return (ERR_DUP);
	return (NULL);
}

const char	*err_mapper(int	code)
{
	const char	*helper = error_helper(code);
	if (helper != NULL)
		return helper;
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
