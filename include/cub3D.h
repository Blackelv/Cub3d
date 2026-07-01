/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:41:50 by kel               #+#    #+#             */
/*   Updated: 2026/07/01 22:48:01 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "/usr/include/X11/X.h" //needed to compile on my machine -ff
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <unistd.h>

# define MAP_CHARS "01NSEW "
# define SPAWN_CHARS "NSEW"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 900
# define FOV 60
# define BLOCK 64
# define SPEED 1
# define ROT 0.05
# define MINI_SCALE 20
# define MAP_RANGE 500
# define DEG_1 0.01745
// # define DOF 40

# define PI 3.1415926535

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
# define ERR_DUP "File contains duplicate element"
# define ERR_SCENERY "Invalid Scene"
# define ERR__PATH_M "File missing path"
# define ERR_PATH_T "Invalid path, contains extras"
# define ERR_F_COLOR "Missing Floor color"
# define ERR_C_COLOR "Missing ceiling color"
# define ERR_MISS_COLOR "Missing colors"
# define ERR_MISS_TEX "Missing textures"
# define ERR_NO_TEX "Missing North texture"
# define ERR_SO_TEX "Missing South texture"
# define ERR_WE_TEX "Missing West texture"
# define ERR_EA_TEX "Missing East texture"
# define ERR_RGB_R "RGB value out of range (0 - 255)"
# define ERR_RGB_F "Invalid RGB format (3 sets of digits separated by ',')"
# define ERR_RGB_M "Missing RGB value"
# define ERR_INVAL_C "Invalid character in map"
# define ERR_MULTI_SPAWN "Multiple spawn positions in map"
# define ERR_NO_SPAWN "No player spawn position (N/S/E/W)"
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

enum			e_errors
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
	E_TEX_ADDR
};

enum			e_scenestate
{
	PRE_MAP,
	IN_MAP,
	AFTER_MAP
};

typedef enum e_textid
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	T_COUNT,
	NONE = -1
}				t_textid;

typedef struct s_flood
{
	char		**grid;
	char		**vis;
	int			*stack;
	int			top;
	int			h;
	int			w;
	int			i;
	int			j;
}				t_flood;

typedef struct s_map
{
	char		**grid;
	char		**raw;
	int r_count; // parse
	int r_cap;   // parse
	int			width;
	int			height;
	int			spawn_x;
	int			spawn_y;
	int spawn_count; // parse
	char		spawn_dir;
	bool parsed;    // parse
	bool has_space; // parse
	bool is_closed; // parse
	int map_range;  // view window of minimap
}				t_map;

typedef struct s_collision
{
	bool		N;
	bool		S;
	bool		E;
	bool		W;

}				t_collision;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		angle;
	t_collision	collision;
}				t_player;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			w;
	int			h;
	int			bpp;
	int			endian;
	int			line_len;
}				t_img;

typedef struct s_assets
{
	t_img		img[T_COUNT];
	char		*path[T_COUNT];
	int			floor;
	int			ceiling;
	bool		f_set;
	bool		c_set;
}				t_assets;

typedef struct xy_point
{
	int			x;
	int			y;
}				t_xy_point;

typedef struct xy_double
{
	double		x;
	double		y;
}				t_xy_double;

typedef struct raycast
{
	float ra; // ray angle
	float x;  // intersection point (r.x & r.y)
	float		y;
	float		dist;
	int wall; // N / E / S / W
}				t_raycast;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_img		frame;
	t_assets	assets;
	t_raycast	raycaster[FOV];
}				t_cub;

//--------------------------------Main FUNCTIONS-------------------------------/

//------------------------------Parsing FUNCTIONS------------------------------/
int				parse_n_init_map(t_cub *cub, char *file);
int				valid_scene(t_cub *cub, char *file);
t_textid		match_type_identifier(char *s);
bool			is_line_empty(char *line);
bool			is_scene_description(char *line);
bool			is_map_content(char *line);
int				fill_scenery(t_cub *cub, char *line);
int				store_map_line(t_cub *cub, const char *line);
int				parse_rgb(const char *s, int *r, int *g, int *b);
int				check_config_complete(t_cub *cub);
int				build_map_grid(t_cub *cub);
int				scan_validate_map(t_cub *cub);
int				init_player_spawn(t_cub *cub);
int				init_mlx(t_cub *cub);
int				check_borders(t_cub *cub);
char			**visited_arr(int h, int w);
void			free_visited_arr(char **vis, int n);
int				flood_borders(t_cub *cub, char **vis);
int				floodfill_void(t_cub *cub, int r, int c, char **vis);

//---------------------------------MLX FUNCTIONS-------------------------------/
int				init_mlx(t_cub *cub);

int				x_press(t_cub **cub);
int				key_release(int keycode, t_cub **cub);
int				key_press(int keycode, t_cub **cub);

//------------------------------RENDER FUNCTIONS-------------------------------/
int				render(t_cub *cub);
void			mini_map_resize(t_cub *cub, char inc);
int				generate_raycast(t_cub *cub);

//-----------------NAV FUNCTIONS-----------------------------------------------/
void			move_player(t_cub **cub, char dir);
void			rotate_player(t_cub **cub, char dir);

//-------------------------------Cleaner FUNCTIONS-----------------------------/
void			simple_error_exit(const char *msg);
void			clean_cub3d(t_cub *cub);
void			clean_mlx_ptrs(t_cub *cub);

//-------------------------------Errors FUNCTIONS------------------------------/
const char		*err_mapper(int code);
int				err_msg(const char *details, int code);
const char		*parsing_errors(int code);

#endif
