/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:42:21 by ann               #+#    #+#             */
/*   Updated: 2022/05/26 19:52:46 by aalsuwai         ###   ########.fr       */
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

/* ----------------------- > >> Colors << < ----------------------- */

# define RED				"\033[0;31m"
# define BLUE				"\033[0;34m"
# define GREEN				"\033[0;32m"
# define YELLOW				"\033[0;33m"
# define PURPLE				"\033[0;35m"
# define LIGHT_BLUE			"\033[0;36m"
# define RESET				"\x1B[0m"

# define RED1				"\033[1;31m"
# define BLUE1				"\033[1;34m"
# define GREEN1				"\033[1;32m"
# define YELLOW1			"\033[1;33m"
# define PURPLE1			"\033[1;35m"
# define LIGHT_BLUE1		"\033[1;36m"

# define RED2				"\033[2;31m"
# define BLUE2				"\033[2;34m"
# define GREEN2				"\033[2;32m"
# define YELLOW2			"\033[2;33m"
# define PURPLE2			"\033[2;35m"
# define LIGHT_BLUE2		"\033[2;36m"

# define RED3				"\033[3;31m"
# define BLUE3				"\033[3;34m"
# define GREEN3				"\033[3;32m"
# define YELLOW3			"\033[3;33m"
# define PURPLE3			"\033[3;35m"
# define LIGHT_BLUE3		"\033[3;36m"

# define HX_WHITE			0xFFFFFF
# define HX_OFF_WHITE		0xBEBEBE
# define HX_PASTEL_PINK		0xF8C8DC
# define HX_PASTEL_GREEN	0xC1E1C1
# define HX_GRASS_GREEN		0x567d46
# define HX_GREEN			0x86DC3D
# define HX_BLACK			0x000000
# define HX_RED				0xFF0000
# define HX_YELLOW			0xFFFF00
# define HX_BLUE			0x0000FF
# define HX_PURPLE			0x9932CC
# define HX_SKY_BLUE		0x87CEEB

# define MINI_WALL_COLOR	0x808080
# define RAY_COLOR			HX_WHITE
# define MINI_WALL_BORDER	HX_BLACK
# define MINI_PLAYER_COLOR	HX_GRASS_GREEN

/* ----------------------- > >> Macros << < ----------------------- */

# define WINDOW_X	1680
# define WINDOW_X_2	840
# define WINDOW_Y	840
# define WINDOW_Y_2	420

# define MINIMAP_X	420
# define MINIMAP_Y	210

# define MINI_OFFSET_X	10
# define MINI_OFFSET_Y	5

# define MINI_BLOCK_SIZE_X	30
# define MINI_BLOCK_SIZE_Y	30
# define MINI_BLOCKS_AROUND	8.0

# define EAST	0
# define WEST	M_PI
# define SOUTH	M_PI_2
# define NORTH	-M_PI_2

# define FOV_DEG 66
# define BUFFER_SIZE 1
# define VISION_DEPTH 15.0

# define NO_COLLISION	0
# define COLLISION_XY	1
# define COLLISION_X	2
# define COLLISION_Y	3

# define SIDE_X 1//test pls
# define SIDE_Y 0

# define ACTUAL_WALL_HEIGHT 1
# define TEXTURE_HEIGHT 64
# define TEXTURE_WIDTH 64

# define WALL_SCALE_FACTOR 1.0

# define WC_OFFSET 0.4

# define MOVEMENT_AMOUNT 0.25
# define ROTATION_AMOUNT 0.1
# define MINI_PLAYER_ICON_SIZE 3
# define NUMBER_OF_RAYS 1680

# define START_SCREEN_PATH "textures/start_n_end/start_screen.xpm"
# define END_SCREEN_PATH "textures/start_n_end/end_screen.xpm"

/* customizable defaults */

# define MINIMAP_DEFAULT 1
# define MOUSE_DEFAULT 0
# define INFO_DEFAULT 1

//YOU CAN OBTAIN THE KEYS BY RUNNING "showkey --ascii"

# ifdef linux
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
#  define ESC_KEY 65307
#  define M_KEY 109
#  define H_KEY 104
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define I_KEY 106
# endif

# ifdef __MACH__
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define LEFT_KEY 123
#  define RIGHT_KEY 124
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define ESC_KEY 53
#  define M_KEY 46
#  define H_KEY 4
#  define C_KEY 8
#  define I_KEY 34
# endif

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

typedef struct s_color
{
	int	transparency;
	int	red;
	int	green;
	int	blue;
}	t_color;

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

typedef struct s_collision
{
	bool		collision_x;
	bool		collision_y;
	t_coord		abs;
	t_vector	step;
	t_vector	temp_pos;
	t_vector	player_direction;
}	t_collision;

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

	int		full_sprite_count;

	int		map_starting_i;

	bool	leaf_is_here;
	bool	map_error;
	bool	map_time;
	bool	extra;
	bool	n;
	bool	s;
	bool	w;
	bool	e;
	bool	f;
	bool	c;
	bool	f_is_texture;
	bool	c_is_texture;

	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;

	char	**map;

	char	*f_color_rgb;
	char	*c_color_rgb;
	int		f_color_rgb_int[3];
	int		c_color_rgb_int[3];

	char	**full_file;
}	t_pars;

typedef struct s_sprite
{
	int			in_screen_count;
	float		z_buffer[WINDOW_X];

	int			*s_order;
	double		*s_distance;

	double		invdet;
	double		trans_x;
	double		trans_y;

	int			sprite_screen_x;
	int			sprite_w;
	int			sprite_h;
	int			y_start_draw;
	int			y_end_draw;
	int			x_start_draw;
	int			x_end_draw;

	t_vector	current_sprite_pos;
	t_vector	player_direction;

	t_coord		*position;
}	t_sprite;

typedef struct s_v_cast
{
	double	x;
	double	y;

	double	step_x;
	double	step_y;

	double	x_direction;
	double	y_direction;

	double	degree;
	double	ray_fixed;

	double	min_x_ray_dir;
	double	max_x_ray_dir;
	double	min_y_ray_dir;
	double	max_y_ray_dir;

	double	new_y_pos;
	double	v_camera_pos;
	double	row_distance;

	int		texture_x;
	int		texture_y;

	double	ray_angle;
}	t_v_cast;

typedef struct s_main
{
	void			*mlx;
	void			*mlx_window;
	void			*mlx_image;
	char			*image_address;
	int				bpp;
	int				endian;
	int				size_line;

	t_pars			*p;
	char			**map;
	int				map_width_max;
	int				map_height;

	t_bresenham		*draw;

	t_coord			player_map_position;
	t_coord			ray_map_position;

	t_vector		player_position;
	double			player_angle;

	double			delta_distance_x;
	double			delta_distance_y;

	double			side_length_x;
	double			side_length_y;
	double			final_side_length;

	double			perpend_wall_dist;

	int				place_wall_at_x;
	unsigned int	wall_height;
	int				wall_width;

	double			depth;

	t_vector		camera_plane;

	t_coord			step;
	t_vector		ray_direction;

	bool			minimap_on;
	bool			side_hit;

	unsigned int	ceiling_color;
	unsigned int	floor_color;

	t_texture		texture[4];
	t_texture		start_screen;
	t_texture		end_screen;
	t_texture		floor_tex;
	t_texture		ceiling_tex;
	t_texture		leaf_dude[9];
	int				leaf_index;

	bool			dont_draw;
	bool			info_panel_on;

	bool			is_using_mouse;

	int				offset;
	double			wall_hit_pos;
	int				texture_x;
	double			texture_y;
	double			step_texture;

	t_color			fog;
	t_color			black;
	t_color			minimap_color;
	double			fog_intensity;

	bool			start_screen_done;
	bool			end_screen_done;

	t_sprite		*sprite;
}	t_main;

/* --------------------- > >> Prototypes << < --------------------- */

/* ----------- ** pars utils ** ------------ */
void			remove_nl(char *str);
int				ft_open_n_free(t_pars *p, char *file_path);
void			free_char_double_pointer(char **str);
void			get_max_x_y(char *file_path, t_pars *p);
void			*ft_calloc_p(size_t count, size_t size);

/* ----------- ** check user input ** ------------ */
bool			has_dot_xpm(char *file_path);
void			user_input_check(int argc, char **argv);
void			rgb_char_to_int(char *char_rgb, int int_rgb[3]);

/* -------------- ** map checks ** --------------- */
void			check_map_content(t_pars *p);
void			check_file_validity(t_pars *p);

/* ----------- ** full map save ** ------------- */
void			init_map_save(char *file_path, t_pars *p);

/* ----------------- ** gnl ** ------------------ */
char			*get_next_line(int fd);

/* --------------- ** drawing ** ---------------- */
void			put_pixel(int x, int y, unsigned int color, t_main *s);
void			draw_circle(int radius, t_coord const *origin, t_main *s);
void			draw_rect(int width, int height, t_coord const *origin, \
				t_main *s);
void			draw_border(int width, int height, t_coord const *origin, \
				t_main *s);
void			draw_vertical_texture(t_coord origin, int *width_height, \
				t_texture const *tex, t_main *s);

/* --------------- ** minimap ** ---------------- */
void			draw_minimap(t_main *s);

/* ------------ ** minimap utils ** -------------- */
bool			check_outside_minimap(int x, int y);
void			make_rect_trans(int *width_height, t_coord const *origin, \
				t_color *color, t_main *s);

/* ---------------- ** hooks ** ----------------- */
int				close_x(t_main *s);
int				key_hooks(int keycode, t_main *s);
int				mouse_perspective(int x, int y, t_main *s);

/* --------------- ** ray cast ** --------------- */
void			cast_rays(t_main *s);

/* ------------- ** ray cast utils ** ----------- */
void			select_fog_intensity(t_main *s);
void			draw_rays_for_minimap(t_main *s);
void			check_n_save_leaf_pos(t_main *s);
void			prepare_to_draw_wall(int texture_index, t_main *s);
void			select_correct_texture(int *texture_index, t_main *s);

/* ---------------- ** line ** ------------------ */
void			draw_line(t_coord start, t_coord end, t_main *s);

/* ---------------- ** redraw ** ---------------- */
void			redraw_window(t_main *s);

/* --------------- ** initiate ** --------------- */
void			initiate_player_info(t_main *s);

/* ---------------- ** math ** ------------------ */
double			deg_to_rad(double deg);
double			rad_to_deg(double rad);
void			rotate_coor(double *x, double *y, double angle);

/* --------------- ** texture ** ---------------- */
void			load_textures(t_pars *p, t_main *s);

/* ---------------- ** color ** ----------------- */
unsigned int	rgb_to_uint(int transp, int red, int green, int blue);
void			uint_to_rgb(unsigned int uint_color, t_color *rgb_color);
void			add_fog(double intensity, t_color fog_color, t_color *color);
void			assign_rgb_color(int red, int green, int blue, t_color *color);
unsigned int	add_fog_uint(double intensity, t_color *fog_color, \
				unsigned int color);

/* --------------- ** collision ** -------------- */
int				check_collision(double move_amount, double change_angle, \
				t_main *s);

/* ---------------- ** toggle ** ---------------- */
void			toggle_mouse(t_main *s);
void			toggle_start_n_draw(t_main *s);
void			toggle_minimap_n_draw(t_main *s);
void			toggle_info_n_draw(t_main *s);

/* -------------- ** animation ** --------------- */
int				animation(t_main *s);
void			draw_sprite(t_main *s, t_texture *tex);
bool			check_sprite_coord(t_main *s, int x, int y);

/* -------------- ** sprite cast ** ------------- */
void			sprite_cast(t_main *s, t_texture *tex);

/* ------------- ** floor ceiling ** ------------ */
void			floor_n_ceiling_cast(t_main *s, t_texture *texture, int y);
void			color_floor(unsigned int color, t_color *fog_color, t_main *s);
void			color_ceiling(unsigned int color, t_color *fog_color, \
				t_main *s);

/* ----------------- ** exit ** ----------------- */
int				close_x(t_main *s);
void			free_double_char(char **array);

#endif