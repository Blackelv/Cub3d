/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:01:36 by kel               #+#    #+#             */
/*   Updated: 2026/03/24 03:18:14 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_correct_name(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (1);
	return (0);
}

int	can_open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	close (fd);
	return (0);
}

int	correct_file(char *file)
{
	if (check_correct_name(file))
		return (E_NAME_KO);
	if (can_open_file(file))
		return (E_OPEN_KO);
	return (0);
}

int	parse_n_init_map(t_cub *cub, char *file)
{
	int	code;

	code = correct_file(file);
	if (code != OK)
		return (err_msg(file, code));
	code = valid_scene(cub, file);
	if (code != OK)
		return (err_msg(file, code));
	code = check_config_complete(cub);
	if (code != OK)
		return (err_msg(file, code));
	code = build_map_grid(cub);
	if (code != OK)
		return (err_msg(file, code));
	code = scan_validate_map(cub);
	if (code != OK)
		return (err_msg(file, code));
	code = init_player_spawn(cub);
	if (code != OK)
		return (err_msg(file, code));
	code = init_mlx(cub);
	if (code != OK)
		return (err_msg(file, code));
	return (OK);
}
