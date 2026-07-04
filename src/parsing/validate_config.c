/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:05:17 by kel               #+#    #+#             */
/*   Updated: 2026/03/23 16:03:49 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	int	missing_scenes(t_cub *cub)
{
	int	t_miss;
	int	c_miss;

	t_miss = 0;
	c_miss = 0;
	if (!cub->assets.path[NORTH])
		t_miss++;
	if (!cub->assets.path[SOUTH])
		t_miss++;
	if (!cub->assets.path[WEST])
		t_miss++;
	if (!cub->assets.path[EAST])
		t_miss++;
	if (!cub->assets.c_set)
		c_miss++;
	if (!cub->assets.f_set)
		c_miss++;
	if (t_miss >= 2)
		return (E_MISS_TEX);
	if (c_miss == 2)
		return (E_MISS_COLOR);
	return (OK);
}

static	int	each_path(char *file)
{
	int		fd;
	size_t	len;
	ssize_t	n;
	char	buf;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".xpm", 4) != 0)
		return (E_XPM_FILE);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (E_OPEN_KO);
	n = read(fd, &buf, 1);
	close (fd);
	if (n == -1)
		return (E_IS_DIR);
	return (OK);
}

static	int	validate_tex_paths(t_cub *cub)
{
	int	code;

	code = each_path(cub->assets.path[NORTH]);
	if (code != OK)
		return (code);
	code = each_path(cub->assets.path[SOUTH]);
	if (code != OK)
		return (code);
	code = each_path(cub->assets.path[WEST]);
	if (code != OK)
		return (code);
	code = each_path(cub->assets.path[EAST]);
	if (code != OK)
		return (code);
	return (OK);
}

static	int	check_missing_map(t_cub *cub)
{
	if (!cub)
		return (E_INVAL_MAP);
	if (cub->map.r_count == 0)
		return (E_NO_MAP);
	return (OK);
}

int	check_config_complete(t_cub *cub)
{
	int	ret;

	ret = missing_scenes(cub);
	if (ret != OK)
		return (ret);
	if (!cub->assets.path[NORTH])
		return (E_MISS_NO);
	if (!cub->assets.path[SOUTH])
		return (E_MISS_SO);
	if (!cub->assets.path[WEST])
		return (E_MISS_WE);
	if (!cub->assets.path[EAST])
		return (E_MISS_EA);
	if (!cub->assets.c_set)
		return (E_MISS_C);
	if (!cub->assets.f_set)
		return (E_MISS_F);
	ret = validate_tex_paths(cub);
	if (ret != OK)
		return (ret);
	ret = check_missing_map(cub);
	if (ret != OK)
		return (ret);
	return (OK);
}
