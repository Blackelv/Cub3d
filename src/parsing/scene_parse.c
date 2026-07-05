/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:12:56 by kel               #+#    #+#             */
/*   Updated: 2026/03/23 13:59:46 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	int	process_pre_map(t_cub *cub, char *line, int *state)
{
	if (is_line_empty(line))
		return (OK);
	if (is_scene_description(line))
		return (fill_scenery(cub, line));
	if (is_map_content(line))
	{
		*state = IN_MAP;
		return (store_map_line(cub, line));
	}
	return (E_PRE_MAP);
}

static	int	process_in_map(t_cub *cub, char *line, int *state)
{
	if (is_line_empty(line))
	{
		*state = AFTER_MAP;
		return (OK);
	}
	if (is_map_content(line))
		return (store_map_line(cub, line));
	return (E_IN_MAP);
}

static	int	process_after_map(t_cub *cub, char *line, int *state)
{
	(void)cub;
	(void)state;
	if (is_line_empty(line))
		return (OK);
	return (E_AFTER_MAP);
}

int	process_line(t_cub *cub, char *line, int *state)
{
	if (*state == PRE_MAP)
		return (process_pre_map(cub, line, state));
	else if (*state == IN_MAP)
		return (process_in_map(cub, line, state));
	else if (*state == AFTER_MAP)
		return (process_after_map(cub, line, state));
	return (OK);
}

int	valid_scene(t_cub *cub, char *file)
{
	int		fd;
	int		code;
	int		state;
	char	*line;

	state = PRE_MAP;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (E_OPEN_KO);
	line = get_next_line(fd);
	while (line)
	{
		line = ft_trimendl(line);
		code = process_line(cub, line, &state);
		if (code != OK)
		{
			free(line);
			return (close(fd), code);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (OK);
}
