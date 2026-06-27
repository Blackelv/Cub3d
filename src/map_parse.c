/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:32:03 by kel               #+#    #+#             */
/*   Updated: 2026/05/17 14:57:15 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	color_paths(t_cub *cub, const char which, const char *str)
{
	int	r;
	int	g;
	int	b;
	int	code;

	if (!str || str[0] == '\0')
		return (E_RGB_MISSING);
	if (which == 'F' && cub->assets.f_set)
		return (E_DUP_KO);
	if (which == 'C' && cub->assets.c_set)
		return (E_DUP_KO);
	code = parse_rgb(str, &r, &g, &b);
	if (code != OK)
		return (code);
	if (which == 'F')
	{
		cub->assets.floor = (r << 16) | (g << 8) | b;
		cub->assets.f_set = true;
	}
	else if (which == 'C')
	{
		cub->assets.ceiling = (r << 16) | (g << 8) | b;
		cub->assets.c_set = true;
	}
	return (OK);
}

int	texture_paths(t_cub *cub, t_textid id, const char *str)
{
	char	**store;
	char	*s_dup;
	int		i;

	if (!str || str[0] == '\0')
		return (E_TEX_PATH_MISSING);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (E_TEX_PATH_TRAILING);
		i++;
	}
	if (id < 0 || id >= T_COUNT)
		return (E_SCENE_KO);
	store = &cub->assets.path[id];
	if (*store)
		return (E_DUP_KO);
	s_dup = ft_strdup(str);
	if (!s_dup)
		return (E_ALLOC_KO);
	*store = s_dup;
	return (OK);
}

int	fill_scenery(t_cub *cub, char *line)
{
	int			i;
	char		which;
	t_textid	t_id;

	i = ft_skip_whitespace(line, 0);
	t_id = match_type_identifier(line + i);
	if (t_id != NONE)
	{
		i += 2;
		while (line[i] && ft_isspace(line[i]))
			i++;
		line = ft_trunc_whitespace(line);
		return (texture_paths(cub, t_id, line + i));
	}
	else if (line[i] == 'F' || line[i] == 'C')
	{
		which = line[i];
		i += 1;
		while (line[i] && ft_isspace(line[i]))
			i++;
		line = ft_trunc_whitespace(line);
		return (color_paths(cub, which, line + i));
	}
	return (E_SCENE_KO);
}

static int	dynamic_resize_mem(t_cub *cub)
{
	char	**new_r;
	int		new_cap;
	int		i;

	if (cub->map.r_count < cub->map.r_cap)
		return (OK);
	if (cub->map.r_cap == 0)
		new_cap = 8;
	else
		new_cap = cub->map.r_cap * 2;
	new_r = malloc(sizeof(*new_r) * (new_cap + 1));
	if (!new_r)
		return (E_ALLOC_KO);
	i = 0;
	while (i < cub->map.r_count)
	{
		new_r[i] = cub->map.raw[i];
		i++;
	}
	new_r[cub->map.r_count] = NULL;
	free(cub->map.raw);
	cub->map.raw = new_r;
	cub->map.r_cap = new_cap;
	return (OK);
}

int	store_map_line(t_cub *cub, const char *line)
{
	char	*s_dup;
	int		len;

	s_dup = ft_strdup(line);
	if (!s_dup)
		return (E_ALLOC_KO);
	if (dynamic_resize_mem(cub) == E_ALLOC_KO)
	{
		free(s_dup);
		return (E_ALLOC_KO);
	}
	cub->map.raw[cub->map.r_count] = s_dup;
	cub->map.r_count++;
	cub->map.raw[cub->map.r_count] = NULL;
	cub->map.height = cub->map.r_count;
	cub->map.map_range = MAP_RANGE;
	len = ft_strlen(s_dup);
	if (len > cub->map.width)
		cub->map.width = len;
	if (ft_strchr(s_dup, ' ') != NULL)
		cub->map.has_space = true;
	return (OK);
}
