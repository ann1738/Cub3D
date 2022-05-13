/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:42:21 by ann               #+#    #+#             */
/*   Updated: 2022/05/13 18:47:28 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ----------------------- > >> Headers << < ---------------------- */

# include "../libft/libft.h"
# include "../mlx_macos/mlx.h"
# include "../mlx_linux/mlx.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

#include <time.h>

/* ----------------------- > >> Colors << < ----------------------- */

# define RED			"\033[0;31m"
# define BLUE			"\033[0;34m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define PURPLE			"\033[0;35m"
# define LIGHT_BLUE		"\033[0;36m"
# define RESET			"\x1B[0m"

# define RED1			"\033[1;31m"
# define BLUE1			"\033[1;34m"
# define GREEN1			"\033[1;32m"
# define YELLOW1		"\033[1;33m"
# define PURPLE1		"\033[1;35m"
# define LIGHT_BLUE1	"\033[1;36m"

# define RED2			"\033[2;31m"
# define BLUE2			"\033[2;34m"
# define GREEN2			"\033[2;32m"
# define YELLOW2		"\033[2;33m"
# define PURPLE2		"\033[2;35m"
# define LIGHT_BLUE2	"\033[2;36m"

# define RED3			"\033[3;31m"
# define BLUE3			"\033[3;34m"
# define GREEN3			"\033[3;32m"
# define YELLOW3		"\033[3;33m"
# define PURPLE3		"\033[3;35m"
# define LIGHT_BLUE3	"\033[3;36m"

# define HX_WHITE 0xFFFFFF
# define HX_OFF_WHITE 0xBEBEBE
# define HX_PASTEL_PINK 0xF8C8DC
# define HX_PASTEL_GREEN 0xC1E1C1
# define HX_GRASS_GREEN 0x567d46
# define HX_GREEN 0x86DC3D
# define HX_BLACK 0x000000
# define HX_RED 0xFF0000
# define HX_YELLOW 0xFFFF00
# define HX_BLUE 0x0000FF
# define HX_PURPLE 0x9932CC
# define HX_SKY_BLUE 0x87CEEB


# define MINI_PLAYER_COLOR HX_GRASS_GREEN
# define MINI_WALL_COLOR HX_PASTEL_PINK
# define MINI_WALL_BORDER HX_BLACK

# define RAY_COLOR HX_RED

// # define FLOOR_COLOR 0x8b5a2b
# define FLOOR_COLOR HX_PASTEL_GREEN
# define CEILING_COLOR HX_SKY_BLUE

/* ----------------------- > >> Macros << < ----------------------- */

# define WINDOW_X 1680
# define WINDOW_Y 840

# define MINIMAP_X 420
# define MINIMAP_Y 210

# define SOUTH M_PI_2
# define NORTH -M_PI_2
# define WEST M_PI
# define EAST 0

# define BUFFER_SIZE 1
# define FOV_DEG 66
# define VISION_DEPTH 15.0

# define SIDE_X true
# define SIDE_Y false

# define ACTUAL_WALL_HEIGHT 1
# define TEXTURE_HEIGHT 64
# define TEXTURE_WIDTH 64

# define WALL_SCALE_FACTOR 2

# define MOVEMENT_AMOUNT 0.25
# define ROTATION_AMOUNT 0.1
# define MINI_PLAYER_ICON_SIZE 5
# define INCREMENT_RAY_CASTING 0.0048

//YOU CAN OBTAIN THE KEYS BY RUNNING "showkey --ascii"

#ifdef linux

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC_KEY 65307
# define M_KEY 109

#endif

#ifdef __MACH__
	# define W_KEY 13
	# define A_KEY 0
	# define S_KEY 1
	# define D_KEY 2
	# define LEFT_KEY 123
	# define RIGHT_KEY 124
	# define ESC_KEY 53
	# define M_KEY 46
#endif

/* ----------------------- > >> Struct << < ----------------------- */

typedef struct s_coord
{
	int				x;
	int				y;
	unsigned int	color;
}	t_coord;

typedef struct s_vector
{
	double			x;
	double			y;
}	t_vector;

// typedef struct s_player
// {
	
// }

typedef struct s_texture
{
	void	*image;
	char	*image_address;
	int		bpp;
	int		endian;
	int		size_line;
	
	int		width;
	int		height;
}	t_texture;


typedef struct s_bresenham{
	int	dy;
	int	dx;
	int	p;
}	t_bresenham;

typedef struct s_pars
{
	int		map_w;
	int		map_h;
	int		file_w;
	int		file_h;

	int		map_starting_i;
	
	bool	map_error;
	bool	map_time;
	bool	extra;
	bool	n;
	bool	s;
	bool	w;
	bool	e;
	bool	f;
	bool	c;

	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;

	char	**map;

	char	*f_color_rgb;
	char	*c_color_rgb;
	int		f_color_rgb_int[3];
	int		c_color_rgb_int[3];
	char	f_color_hex[7];
	char	c_color_hex[7];

	char	**full_file;
}	t_pars;

typedef struct s_main
{
	//mlx info
	void	*mlx;
	void	*mlx_window;
	void	*mlx_image;
	char	*image_address;
	int		bpp;
	int		endian;
	int		size_line;
	//parse
	char	**map;
	int		map_width_max;
	int		map_height;
	//minimap
	int		mini_width_unit;
	int		mini_height_unit;
	//line
	t_bresenham *draw;
	//player
	//player position based on the coordinate of which grid box the player is in
	t_coord		player_map_position;
	t_coord		ray_map_position;
	//player position based on the coordinate of which grid box the player is in but with decimal (to show within the box)
	t_vector	player_position; 
	//player direction from the player position
	double		player_angle;
	// t_vector	player_direction;
	//distance of the ray (accounting for its direction) to traverse one x and y unit
	double		delta_distance_x;
	double		delta_distance_y;
	//side length: the length of the ray to hit the x or y side of a wall
	double		side_length_x;
	double		side_length_y;
	double		final_side_length;
	//calculate the perpendicular wall distance (will be used to draw the vertical wall strips)
	double		perpend_wall_dist;
	//where to draw the vertical strip walls
	int			place_wall_at_x;
	unsigned int	wall_height;
	int			wall_width;
	//depth of the player's vision
	double		depth;
	//projection plane
	double	dist_to_projection_plane;
	t_vector	camera_plane;

	t_coord		step;
	t_vector	ray_direction;

	bool	minimap_on;
	bool	side_hit;

	//fps
	clock_t	frame1;
	clock_t	frame2;
	double	fps;

	//colors
	unsigned int	ceiling_color;
	unsigned int	floor_color;

	//texture
	t_texture	texture[6];

	//
	bool	dont_draw;

	int	offset;
	double	wall_hit_pos; //will be used for textures
	int	texture_x;
	double	texture_y;
	double	step_texture;
	
	
}	t_main;

/* --------------------- > >> Prototypes << < --------------------- */

/* ----------- ** pars utils ** ------------ */
void	remove_nl(char *str);
void	free_char_double_pointer(char **str);
void	get_max_x_y(char *file_path, t_pars *p);
int		rgb_to_uint(int transp, int red, int green, int blue);

/* ----------- ** check user input ** ------------ */
void	user_input_check(int argc, char **argv);

/* -------------- ** map checks ** --------------- */
void	check_map_content(t_pars *p);
void	check_file_validity(t_pars *p);

/* ----------- ** full map save ** ------------- */
void	init_map_save(char *file_path, t_pars *p);

/* ------------- ** rgb to hex ** -------------- */
void	rgb_char_to_int(char *char_rgb, int int_rgb[3]);
void	rgb_to_hex(int rgb_int[3], char *hex);

/* ----------------- ** gnl ** ------------------ */
char	*get_next_line(int fd);

/* -------------- ** temp parse ** -------------- */

int		get_y(char *file);
char	**save_map(char **map, char *file, int x);

/* --------------- ** drawing ** ---------------- */
void	put_pixel(int x, int y, unsigned int color, t_main *s);
void	draw_rect(int width, int height, t_coord const *origin, t_main *s);
void	draw_border(int width, int height, t_coord const *origin, t_main *s);
void	draw_circle(int radius, t_coord const *origin, t_main *s);
void	draw_vertical_strip(t_coord origin, int width, int height, t_main *s);
void	draw_vertical_texture(t_coord origin, int width, int height, t_texture const *tex, t_main *s);

/* --------------- ** minimap ** ---------------- */

void	draw_minimap(t_main *s);

/* ---------------- ** hooks ** ----------------- */

int		key_hooks(int keycode, t_main *s);
int		close_x(int keycode, t_main *s);

void	rotate_coor(double *x, double *y, double angle);

/* --------------- ** ray cast ** --------------- */

void	cast_rays(t_main *s);

/* ---------------- ** line ** ------------------ */

void	draw_line(t_coord start, t_coord end, t_main *s);

/* ---------------- ** floor ** ----------------- */

void	draw_floor(unsigned int color, t_main *s);

/* ---------------- ** ceiling ** --------------- */

void	draw_ceiling(unsigned int color, t_main *s);

/* ---------------- ** redraw ** ---------------- */

void	redraw_window(t_main *s);

/* --------------- ** initiate ** --------------- */

void	initiate_player_info(t_main *s);

/* ---------------- ** math ** ------------------ */

double	deg_to_rad(double deg);
double	rad_to_deg(double rad);

/* --------------- ** texture ** ---------------- */

void	load_textures(t_pars *p, t_main *s);

/* ---------------- ** math ** ------------------ */

void	fps(t_main *s);

#endif