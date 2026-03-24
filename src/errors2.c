/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 03:26:29 by kel               #+#    #+#             */
/*   Updated: 2026/03/24 03:29:02 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

const char	*parsing_errors(int code)
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
