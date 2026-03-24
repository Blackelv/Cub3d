/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:01:01 by kel               #+#    #+#             */
/*   Updated: 2026/03/23 15:46:17 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_textid	match_type_identifier(char *s)
{
	if (s == NULL || s[0] == '\0' || s[1] == '\0')
		return (NONE);
	if (s[0] == 'N' && s[1] == 'O')
		return (NORTH);
	if (s[0] == 'S' && s[1] == 'O')
		return (SOUTH);
	if (s[0] == 'W' && s[1] == 'E')
		return (WEST);
	if (s[0] == 'E' && s[1] == 'A')
		return (EAST);
	return (NONE);
}

bool	is_line_empty(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (true);
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else
			return (false);
	}
	return (true);
}

static	bool	is_texture_format(char *line, int i)
{
	int	j;

	if (!line[i + 2] || !ft_isspace(line[i + 2]))
		return (false);
	j = i + 2;
	while (line[j] && ft_isspace(line[j]))
		j++;
	return (line[j] != '\0');
}

bool	is_scene_description(char *line)
{
	int			i;
	int			j;
	t_textid	tex;

	i = 0;
	if (line == NULL)
		return (false);
	i = ft_skip_whitespace(line, 0);
	tex = match_type_identifier(line + i);
	if (tex != NONE)
		return (is_texture_format(line, i));
	if (line[i] == 'F' || line[i] == 'C')
	{
		if (!line[i + 1] || !ft_isspace(line[i + 1]))
			return (false);
		j = i + 1;
		while (line[j] && ft_isspace(line[j]))
			j++;
		return (line[j] != '\0');
	}
	return (false);
}

bool	is_map_content(char *line)
{
	int		i;
	bool	flag;

	if (!line)
		return (false);
	i = 0;
	flag = false;
	while (line[i])
	{
		if (line[i] == '\r' && line[i + 1] == '\0')
			break ;
		if (ft_strchr(MAP_CHARS, line[i]) == NULL)
			return (false);
		if (line[i] != ' ')
			flag = true;
		i++;
	}
	return (flag);
}
