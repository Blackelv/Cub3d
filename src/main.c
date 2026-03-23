/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:49:28 by kel               #+#    #+#             */
/*   Updated: 2026/03/23 00:37:29 by kel              ###   ########.fr       */
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

bool	is_scene_description(char *line)
{
	int			i;
	int			j;
	t_textid	tex;

	i = 0;
	if (line == NULL)
		return (false);
	while (line[i] && ft_isspace(line[i]))
		i++;
	tex = match_type_identifier(line + i);
	if (tex != NONE)
	{
		if (!line[i + 2] || !ft_isspace(line[i + 2]))
			return (false);
		j = i + 2;
		while (line[j] && ft_isspace(line[j]))
			j++;
		return (line[j] != '\0');
	}
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

char	*ft_chomp_whitespace(char *str)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while (len > 0 && ft_isspace(str[len - 1]))
	{
		str[len - 1] = '\0';
		len--;
	}
	return (str);
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

int	get_number(const char *s, int *i, int *val)
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

int	skip_whitespace(const char *str, int i)
{
	if (!str)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

int	parse_rgb(const char *s, int *r, int *g, int *b)
{
	int	i;
	int	code;

	i = 0;
	i = skip_whitespace(s, i);
	code = get_number(s, &i, r);
	if (code != OK)
		return (code);
	i = skip_whitespace(s, i);
	if (s[i] != ',')
		return (E_RGB_FORMAT);
	i++;
	i = skip_whitespace(s, i);
	code = get_number(s, &i, g);
	if (code != OK)
		return (code);
	i = skip_whitespace(s, i);
	if (s[i] != ',')
		return (E_RGB_FORMAT);
	i++;
	i = skip_whitespace(s, i);
	code = get_number(s, &i, b);
	if (code != OK)
		return (code);
	i = skip_whitespace(s, i);
	if (s[i] != '\0')
		return (E_RGB_FORMAT);
	return (OK);
}

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

int	fill_scenery(t_cub *cub, char *line)
{
	int			i;
	char		which;
	t_textid	t_id;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	t_id = match_type_identifier(line + i);
	if (t_id != NONE)
	{
		i += 2;
		while (line[i] && ft_isspace(line[i]))
			i++;
		line = ft_chomp_whitespace(line);
		return (texture_paths(cub, t_id, line + i));
	}
	else if (line[i] == 'F' || line[i] == 'C')
	{
		which = line[i];
		i += 1;
		while (line[i] && ft_isspace(line[i]))
			i++;
		line = ft_chomp_whitespace(line);
		return (color_paths(cub, which, line + i));
	}
	return (E_SCENE_KO);
}

int	store_map_line(t_cub *cub, const char *line)
{
	char	*s_dup;
	char	**new_r;
	int		new_cap;
	int		len;
	int		i;

	s_dup = ft_strdup(line);
	if (!s_dup)
		return (E_ALLOC_KO);
	if (cub->map.r_count == cub->map.r_cap)
	{
		if (cub->map.r_cap == 0)
			new_cap = 8;
		else
			new_cap = cub->map.r_cap * 2;
		new_r = malloc(sizeof(*new_r) * (new_cap + 1));
		if (!new_r)
			return (free(s_dup), E_ALLOC_KO);
		i = 0;
		while (i < cub->map.r_count)
		{
			new_r[i] = cub->map.raw[i];
			i++;
		}
		new_r[cub->map.r_count] = NULL;
		free (cub->map.raw);
		cub->map.raw = new_r;
		cub->map.r_cap = new_cap;
	}
	cub->map.raw[cub->map.r_count] = s_dup;
	cub->map.r_count++;
	cub->map.raw[cub->map.r_count] = NULL;
	cub->map.height = cub->map.r_count;
	len = ft_strlen(s_dup);
	if (len > cub->map.width)
		cub->map.width = len;
	if (ft_strchr(s_dup, ' ') != NULL)
		cub->map.has_space = true;
	return (OK);
}

int	process_line(t_cub *cub, char *line, int *state)
{
	if (*state == PRE_MAP)
	{
		if (is_line_empty(line) == true)
			return (OK);
		if (is_scene_description(line) == true)
			return (fill_scenery(cub, line));
		if (is_map_content(line) == true)
		{
			*state = IN_MAP;
			return (store_map_line(cub, line));
		}
		return (E_PRE_MAP);
	}
	else if (*state == IN_MAP)
	{
		if (is_line_empty(line) == true)
		{
			*state = AFTER_MAP;
			return (OK);
		}
		if (is_map_content(line) == true)
			return (store_map_line(cub, line));
		return (E_IN_MAP);
	}
	else if (*state == AFTER_MAP)
	{
		if (is_line_empty(line) == true)
			return (OK);
		return (E_AFTER_MAP);
	}
	return (OK);
}

char	*ft_trimendl(char *str)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
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

int	missing_scenes(t_cub *cub)
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

int	check_missing_map(t_cub *cub)
{
	if (!cub)
		return (E_INVAL_MAP);
	if (cub->map.r_count == 0)
		return (E_NO_MAP);
	return (OK);
}

int	each_path(char *file)
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

int	validate_tex_paths(t_cub *cub)
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

int	build_map_grid(t_cub *cub)
{
	int	i;
	int	len;

	if (!cub || !cub->map.raw || cub->map.r_count == 0 || cub->map.width <= 0)
		return (E_INVAL_MAP);
	cub->map.grid = malloc(sizeof(*cub->map.grid) * (cub->map.r_count + 1));
	if (!cub->map.grid)
		return (E_ALLOC_KO);
	i = 0;
	while (i < cub->map.r_count)
	{
		cub->map.grid[i] = malloc(cub->map.width + 1);
		if (!cub->map.grid[i])
		{
			while (i-- > 0)
				free(cub->map.grid[i]);
			free(cub->map.grid);
			cub->map.grid = NULL;
			return (E_ALLOC_KO);
		}
		len = ft_strlen(cub->map.raw[i]);
		ft_strlcpy(cub->map.grid[i], cub->map.raw[i], cub->map.width + 1);
		while (len < cub->map.width)
		{
			cub->map.grid[i][len] = ' ';
			len++;
		}
		cub->map.grid[i][cub->map.width] = '\0';
		i++;
	}
	cub->map.grid[i] = NULL;
	cub->map.height = cub->map.r_count;
	cub->map.parsed = true;
	return (OK);
}

int	valid_chars(t_cub *cub)
{
	int	col;
	int	row;

	row = 0;
	while (row < cub->map.height)
	{
		col = 0;
		while (col < cub->map.width)
		{
			if (ft_strchr(MAP_CHARS, cub->map.grid[row][col]) == NULL)
				return (E_BAD_CHAR);
			col++;
		}
		row++;
	}
	return (OK);
}

int	valid_spawns(t_cub *cub)
{
	int	col;
	int	row;

	row = 0;
	cub->map.spawn_count = 0;
	while (row < cub->map.height)
	{
		col = 0;
		while (col < cub->map.width)
		{
			if (ft_strchr(SPAWN_CHARS, cub->map.grid[row][col]) != NULL)
			{
				cub->map.spawn_count++;
				if (cub->map.spawn_count > 1)
					return (E_MULTI_SPAWN);
				cub->map.spawn_x = col;
				cub->map.spawn_y = row;
				cub->map.spawn_dir = cub->map.grid[row][col];
				cub->map.grid[row][col] = '0';
			}
			col++;
		}
		row++;
	}
	if (cub->map.spawn_count == 0)
		return (E_NO_SPAWN);
	return (OK);
}

int	check_top_bottom_rows(t_cub *cub)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (col < cub->map.width)
	{
		if (cub->map.grid[row][col] != '1' && cub->map.grid[row][col] != ' ')
			return (E_MAP_OPEN);
		col++;
	}
	row = cub->map.height - 1;
	col = 0;
	while (col < cub->map.width)
	{
		if (cub->map.grid[row][col] != '1' && cub->map.grid[row][col] != ' ')
			return (E_MAP_OPEN);
		col++;
	}
	return (OK);
}

int	check_left_right_cols(t_cub *cub)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (row < cub->map.height)
	{
		if (cub->map.grid[row][col] != '1' && cub->map.grid[row][col] != ' ')
			return (E_MAP_OPEN);
		row++;
	}
	col = cub->map.width - 1;
	row = 0;
	while (row < cub->map.height)
	{
		if (cub->map.grid[row][col] != '1' && cub->map.grid[row][col] != ' ')
			return (E_MAP_OPEN);
		row++;
	}
	return (OK);
}

int	check_borders(t_cub *cub)
{
	int	code;

	code = check_top_bottom_rows(cub);
	if (code != OK)
		return (code);
	code = check_left_right_cols(cub);
	if (code != OK)
		return (code);
	return (OK);
}

char	**visited_arr(int h, int w)
{
	char	**vis;
	int		i;

	vis = ft_calloc(h, sizeof(char *));
	if (!vis)
		return (NULL);
	i = 0;
	while (i < h)
	{
		vis[i] = ft_calloc(w, sizeof(char));
		if (!vis[i])
		{
			while (i-- > 0)
				free(vis[i]);
			free(vis);
			return (NULL);
		}
		i++;
	}
	return (vis);
}

void	free_visited_arr(char **vis, int n)
{
	int	i;

	if (!vis)
		return ;
	i = 0;
	while (i < n)
	{
		free(vis[i]);
		i++;
	}
	free(vis);
}

// int	coords_in_bound(int i, int j, int h, int w)
// {
// 	return (i >= 0 && i < h && j >= 0 && j < w);
// }

// int	eval_prox_cell(char **grid, char **vis, int i, int j)
// {
// 	if (grid[i][j] == '0')
// 		return (-1);
// 	if (grid[i][j] == ' ' && vis[i][j] == 0)
// 		return (1);
// 	return (0);
// }

// int	floodfill_void(t_cub *cub, int r, int c, char **vis)
// {
// 	int	i;
// 	int	j;
// 	int	idx;
// 	int	top;
// 	int	*stack;

// 	stack = malloc(sizeof(int) * (cub->map.height * cub->map.width));
// 	if (!stack)
// 		return (E_ALLOC_KO);
// 	top = 0;
// 	stack[top] = r * cub->map.width + c;
// 	top++;
// 	while (top > 0)
// 	{
// 		top--;
// 		idx = stack[top];
// 		i = idx / cub->map.width;
// 		j = idx % cub->map.width;
// 		if (vis[i][j] == 1)
// 			continue ;
// 		vis[i][j] = 1;
// 		if (coords_in_bound(i - 1, j, cub->map.height, cub->map.width))
// 		{
// 			if (eval_prox_cell(cub->map.grid, vis, i - 1, j) == -1)
// 				return (free(stack), E_MAP_OPEN);
// 			if (eval_prox_cell(cub->map.grid, vis, i - 1, j) == 1)
// 				stack[top++] = (i - 1) * cub->map.width + j;
// 		}
// 		if (coords_in_bound(i + 1, j, cub->map.height, cub->map.width))
// 		{
// 			if (eval_prox_cell(cub->map.grid, vis, i + 1, j) == -1)
// 				return (free(stack), E_MAP_OPEN);
// 			if (eval_prox_cell(cub->map.grid, vis, i + 1, j) == 1)
// 				stack[top++] = (i + 1) * cub->map.width + j;
// 		}
// 		if (coords_in_bound(i, j - 1, cub->map.height, cub->map.width))
// 		{
// 			if (eval_prox_cell(cub->map.grid, vis, i, j - 1) == -1)
// 				return (free(stack), E_MAP_OPEN);
// 			if (eval_prox_cell(cub->map.grid, vis, i, j - 1) == 1)
// 				stack[top++] = i * cub->map.width + (j - 1);
// 		}
// 		if (coords_in_bound(i, j + 1, cub->map.height, cub->map.width))
// 		{
// 			if (eval_prox_cell(cub->map.grid, vis, i, j + 1) == -1)
// 				return (free(stack), E_MAP_OPEN);
// 			if (eval_prox_cell(cub->map.grid, vis, i, j + 1) == 1)
// 				stack[top++] = i * cub->map.width + (j + 1);
// 		}
// 	}
// 	free(stack);
// 	return (OK);
// }

int	init_t_flood(t_flood *f, t_cub *cub, char **vis)
{
	f->grid = cub->map.grid;
	f->vis = vis;
	f->h = cub->map.height;
	f->w = cub->map.width;
	f->stack = malloc(sizeof(int) * (cub->map.height * cub->map.width));
	if (!f->stack)
		return (E_ALLOC_KO);
	f->top = 0;
	return (OK);
}

int	flood_next_cell(t_flood *f, int ni, int nj)
{
	int	idx;

	if (ni < 0 || ni >= f->h || nj < 0 || nj >= f->w)
		return (OK);
	if (f->grid[ni][nj] == '0')
		return (E_MAP_OPEN);
	if (f->grid[ni][nj] == ' ' && f->vis[ni][nj] == 0)
	{
		idx = ni * f->w + nj;
		f->stack[f->top] = idx;
		f->top++;
	}
	return (OK);
}

int	floodfill_void(t_cub *cub, int r, int c, char **vis)
{
	t_flood	f;
	int		i;
	int		j;
	int		idx;

	if (init_t_flood(&f, cub, vis) != OK)
		return (E_ALLOC_KO);
	f.stack[f.top] = r * f.w + c;
	f.top++;
	while (f.top > 0)
	{
		idx = f.stack[--f.top];
		i = idx / f.w;
		j = idx % f.w;
		if (f.vis[i][j] == 1)
			continue ;
		f.vis[i][j] = 1;
		if (flood_next_cell(&f, i - 1, j) != OK)
			return (free(f.stack), E_MAP_OPEN);
		if (flood_next_cell(&f, i + 1, j) != OK)
			return (free(f.stack), E_MAP_OPEN);
		if (flood_next_cell(&f, i, j - 1) != OK)
			return (free(f.stack), E_MAP_OPEN);
		if (flood_next_cell(&f, i, j + 1) != OK)
			return (free(f.stack), E_MAP_OPEN);
	}
	free(f.stack);
	return (OK);
}

int	top_bottom_flood(t_cub *cub, char **vis)
{
	int	r;
	int	c;
	int	code;

	c = 0;
	while (c < cub->map.width)
	{
		r = 0;
		if (cub->map.grid[r][c] == ' ' && vis[r][c] == 0)
		{
			code = floodfill_void(cub, r, c, vis);
			if (code != OK)
				return (code);
		}
		r = cub->map.height - 1;
		if (cub->map.grid[r][c] == ' ' && vis[r][c] == 0)
		{
			code = floodfill_void(cub, r, c, vis);
			if (code != OK)
				return (code);
		}
		c++;
	}
	return (OK);
}

int	left_right_flood(t_cub *cub, char **vis)
{
	int	r;
	int	c;
	int	code;

	r = 0;
	while (r < cub->map.height)
	{
		c = 0;
		if (cub->map.grid[r][c] == ' ' && vis[r][c] == 0)
		{
			code = floodfill_void(cub, r, c, vis);
			if (code != OK)
				return (code);
		}
		c = cub->map.width - 1;
		if (cub->map.grid[r][c] == ' ' && vis[r][c] == 0)
		{
			code = floodfill_void(cub, r, c, vis);
			if (code != OK)
				return (code);
		}
		r++;
	}
	return (OK);
}

int	flood_borders(t_cub *cub, char **vis)
{
	int	code;

	if (cub->map.height <= 0 || cub->map.width <= 0 || !vis)
		return (E_INVAL_MAP);
	code = top_bottom_flood(cub, vis);
	if (code != OK)
		return (code);
	code = left_right_flood(cub, vis);
	if (code != OK)
		return (code);
	return (OK);
}

int	map_is_closed(t_cub *cub)
{
	char	**vis;
	int		code;

	if (cub->map.height <= 0 || cub->map.width <= 0)
		return (E_INVAL_MAP);
	if (check_borders(cub))
		return (E_MAP_OPEN);
	vis = visited_arr(cub->map.height, cub->map.width);
	if (!vis)
		return (E_ALLOC_KO);
	code = flood_borders(cub, vis);
	if (code != OK)
	{
		free_visited_arr(vis, cub->map.height);
		return (code);
	}
	free_visited_arr(vis, cub->map.height);
	return (OK);
}

int	scan_validate_map(t_cub *cub)
{
	int	code;

	if (!cub || !cub->map.grid)
		return (E_INVAL_MAP);
	code = valid_chars(cub);
	if (code != OK)
		return (code);
	code = valid_spawns(cub);
	if (code != OK)
		return (code);
	code = map_is_closed(cub);
	if (code != OK)
		return (code);
	return (OK);
}

int	set_spawn_directions(t_cub *cub)
{
	if (cub->map.spawn_dir == 'N')
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = -1;
	}
	else if (cub->map.spawn_dir == 'S')
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = +1;
	}
	else if (cub->map.spawn_dir == 'E')
	{
		cub->player.dir_x = +1;
		cub->player.dir_y = 0;
	}
	else if (cub->map.spawn_dir == 'W')
	{
		cub->player.dir_x = -1;
		cub->player.dir_y = 0;
	}
	else
		return (E_NO_SPAWN);
	return (OK);
}

int	init_player_spawn(t_cub *cub)
{
	int	code;

	if (!cub || cub->map.spawn_count != 1)
		return (E_INVAL_MAP);
	cub->player.x = cub->map.spawn_x + 0.5;
	cub->player.y = cub->map.spawn_y + 0.5;
	code = set_spawn_directions(cub);
	if (code != OK)
		return (code);
	cub->player.plane_x = -cub->player.dir_y * 0.66;
	cub->player.plane_y = cub->player.dir_x * 0.66;
	return (OK);
}

void	destroy_each_tex(t_cub *cub, t_textid idx)
{
	if (cub->assets.img[idx].img)
		mlx_destroy_image(cub->mlx, cub->assets.img[idx].img);
	cub->assets.img[idx].img = NULL;
	cub->assets.img[idx].addr = NULL;
	cub->assets.img[idx].w = 0;
	cub->assets.img[idx].h = 0;
	cub->assets.img[idx].bpp = 0;
	cub->assets.img[idx].line_len = 0;
	cub->assets.img[idx].endian = 0;
}

int	init_each_texture(t_cub *cub, t_textid idx)
{
	int		w;
	int		h;

	cub->assets.img[idx].img = mlx_xpm_file_to_image(cub->mlx,
			cub->assets.path[idx], &w, &h);
	if (!cub->assets.img[idx].img)
		return (E_TEX_IMG);
	cub->assets.img[idx].w = w;
	cub->assets.img[idx].h = h;
	cub->assets.img[idx].addr = mlx_get_data_addr(cub->assets.img[idx].img,
			&cub->assets.img[idx].bpp, &cub->assets.img[idx].line_len,
			&cub->assets.img[idx].endian);
	if (!cub->assets.img[idx].addr)
	{
		ft_putstr_fd("Texture: ", 2);
		ft_putstr_fd(cub->assets.path[idx], 2);
		destroy_each_tex(cub, idx);
		return (E_TEX_ADDR);
	}
	return (OK);
}

int	load_textures(t_cub *cub)
{
	int	i;
	int	j;
	int	code;

	i = 0;
	while (i < T_COUNT)
	{
		code = init_each_texture(cub, i);
		if (code != OK)
		{
			j = 0;
			while (j < i)
			{
				destroy_each_tex(cub, j);
				j++;
			}
			return (code);
		}
		i++;
	}
	return (OK);
}

int	init_mlx(t_cub *cub)
{
	int	code;

	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (E_MLX_PTR);
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!cub->win)
		return (E_WIN_PTR);
	cub->frame.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->frame.img)
		return (E_IMG_PTR);
	cub->frame.addr = mlx_get_data_addr(cub->frame.img, &cub->frame.bpp,
			&cub->frame.line_len, &cub->frame.endian);
	if (!cub->frame.addr)
		return (E_ADDR_PTR);
	code = load_textures(cub);
	if (code != OK)
		return (code);
	return (OK);
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

int	main(int ac, char *av[])
{
	t_cub	*cub;

	if (ac != 2)
		simple_error_exit(ERR_ARGS);
	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		simple_error_exit(ERR_MALLOC);
	if (parse_n_init_map(cub, av[1]))
	{
		clean_cub3d(cub);
		free(cub);
		exit(EXIT_FAILURE);
	}
	clean_cub3d(cub);
	free(cub);
	return (0);
}
