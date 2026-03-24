/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:02:01 by kel               #+#    #+#             */
/*   Updated: 2026/03/23 15:44:00 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	int	get_number(const char *s, int *i, int *val)
{
	int	j;
	int	res;

	j = *i;
	if (!ft_isdigit(s[j]))
		return (E_RGB_FORMAT);
	res = 0;
	while (ft_isdigit(s[j]))
	{
		res = res * 10 + (s[j] - '0');
		if (res > 255)
			return (E_RGB_RANGE);
		j++;
	}
	*val = res;
	*i = j;
	return (OK);
}

static	int	extract_color_code(const char *s, int *i, int *val, char sep)
{
	int	code;

	*i = ft_skip_whitespace(s, *i);
	code = get_number(s, i, val);
	if (code != OK)
		return (code);
	*i = ft_skip_whitespace(s, *i);
	if (sep == ',')
	{
		if (s[*i] != ',')
			return (E_RGB_FORMAT);
		(*i)++;
	}
	else if (sep == '\0')
		if (s[*i] != '\0')
			return (E_RGB_FORMAT);
	return (OK);
}

int	parse_rgb(const char *s, int *r, int *g, int *b)
{
	int	i;
	int	code;

	i = 0;
	code = extract_color_code(s, &i, r, ',');
	if (code != OK)
		return (code);
	code = extract_color_code(s, &i, g, ',');
	if (code != OK)
		return (code);
	code = extract_color_code(s, &i, b, '\0');
	if (code != OK)
		return (code);
	return (OK);
}
