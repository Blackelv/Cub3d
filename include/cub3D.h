/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:41:50 by kel               #+#    #+#             */
/*   Updated: 2026/03/23 00:32:33 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>

# define MAP_CHARS "01NSEW "
# define SPAWN_CHARS "NSEW"
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080


# define ERR_ARGS "Invalid number of args"
# define ERR_PARSE "Failed parsing args"
# define ERR_CUB_FILE "File must have a .cub extension"
# define ERR_XPM_FILE "File must have a .xpm extension"
# define ERR_OPEN_FILE "Failed to open file"
# define ERR_DIR "Is a directory"
# define ERR_MALLOC "Failed memory allocation"
# define ERR_PRE_MAP "Invalid line before map"
# define ERR_IN_MAP "Invalid map content"
# define ERR_MAP_LAST "Map content must be last"
# define ERR_INVALID_MAP "Invalid map"
# define ERR_MISS_MAP "Missing map"
# define ERR_DUP "Invalid, contains duplicate element"
# define ERR_SCENERY "Invalid Scene"
# define ERR__PATH_M "Invalid, missing path"
# define ERR_PATH_T "Invalid, path contains extras"
# define ERR_F_COLOR "Missing Floor color"
# define ERR_C_COLOR "Missing ceiling color"
# define ERR_MISS_COLOR "Missing colors"
# define ERR_MISS_TEX "Missing textures"
# define ERR_NO_TEX "Missing North texture"
# define ERR_SO_TEX "Missing south texture"
# define ERR_WE_TEX "Missing west texture"
# define ERR_EA_TEX "Missing east texture"
# define ERR_RGB_R "RGB value out of range (0 - 255)"
# define ERR_RGB_F "Invalid RGB format (3 sets of digits separated by ',')" 
# define ERR_RGB_M "Missing RGB value"
# define ERR_INVAL_C "Invalid character in map"
# define ERR_MULTI_SPAWN "Multiple spwan positions in map"
# define ERR_NO_SPAWN "No player spwan position (N/S/E/W)"
# define ERR_HOLE_MAP "Map is not closed by walls"
# define ERR_MLX_PTR "Failed to initialize MLX"
# define ERR_MLX_IMG "Failed to create MLX image"
# define ERR_WIN_PTR "Failed to create MLX window"
# define ERR_IMG_PTR "Failed to create frame buffer image"
# define ERR_IMG_ADDR "Failed to get frame buffer address"
# define ERR_TEX_IMG "Failed to load texture image"
# define ERR_TEX_ADDR "Failed to get texture image address"
# define GENERIC_ERR "Generic error"
// # define ERR_FILE_IS_DIR "Is a directory"

enum e_errors
{
	OK = 0,
	KO = 1,
	E_NAME_KO,
	E_OPEN_KO,
	E_IS_DIR,
	E_XPM_FILE,
	E_ALLOC_KO,
	E_INVAL_MAP,
	E_NO_MAP,
	E_SCENE_KO,
	E_DUP_KO,
	E_PRE_MAP,
	E_IN_MAP,
	E_AFTER_MAP,
	E_TEX_PATH_MISSING,
	E_TEX_PATH_TRAILING,
	E_RGB_MISSING,
	E_RGB_FORMAT,
	E_RGB_RANGE,
	E_MISS_NO,
	E_MISS_SO,
	E_MISS_WE,
	E_MISS_EA,
	E_MISS_TEX,
	E_MISS_COLOR,
	E_MISS_F,
	E_MISS_C,
	E_BAD_CHAR,
	E_MULTI_SPAWN,
	E_NO_SPAWN,
	E_MAP_OPEN,
	E_MLX_PTR,
	E_MLX_IMG, 
	E_WIN_PTR,
	E_IMG_PTR,
	E_ADDR_PTR,
	E_TEX_IMG,
	E_TEX_ADDR,
};

enum e_scenestate
{
	PRE_MAP = 15,
	IN_MAP = 16,
	AFTER_MAP = 17
};

typedef enum e_textid
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	T_COUNT,
	NONE = -1
}	t_textid;

typedef struct s_flood
{
	char	**grid;
	char	**vis;
	int		*stack;
	int		top;
	int		h;
	int		w;
	int		i;
	int		j;
}	t_flood;

typedef struct s_map
{
	char	**grid;
	char	**raw;
	int		r_count;
	int		r_cap;
	int		width;
	int		height;
	int		spawn_x;
	int		spawn_y;
	int		spawn_count;
	char	spawn_dir;
	bool	parsed;
	bool	has_space;
	bool	is_closed;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_assets
{
	t_img	img[T_COUNT];
	char	*path[T_COUNT];
	int		floor;
	int		ceiling;
	bool	f_set;
	bool	c_set;
}	t_assets;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_img		frame;
	t_assets	assets;
}	t_cub;

//--------------------------------Main FUNCTIONS-------------------------------/


//-------------------------------Cleaner FUNCTIONS-----------------------------/
void	simple_error_exit(const char *msg);
void	clean_cub3d(t_cub *cub);

//-------------------------------Errors FUNCTIONS------------------------------/
const char	*err_mapper(int	code);
int			err_msg(const char *details, int code);

#endif
