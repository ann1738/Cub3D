/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:42:21 by ann               #+#    #+#             */
/*   Updated: 2022/05/08 22:53:32 by ann              ###   ########.fr       */
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
# define HX_GRASS_GREEN 0x7CFC00
# define HX_GREEN 0x86DC3D
# define HX_BLACK 0x000000
# define HX_RED 0xFF0000
# define HX_BLUE 0x0000FF

# define MINI_BG_COLOR HX_GREEN
# define MINI_PLAYER_COLOR HX_BLUE
# define MINI_WALL_COLOR HX_PASTEL_PINK
# define RAY_COLOR HX_RED

/* ----------------------- > >> Macros << < ----------------------- */

# define WINDOW_X 1680
# define WINDOW_Y 840

# define MINIMAP_X 420
# define MINIMAP_Y 210

# define BUFFER_SIZE 1

//YOU CAN OBTAIN THE KEYS BY RUNNING "showkey --ascii"

#ifdef linux

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65363
# define RIGHT_KEY 65361
# define ESC_KEY 65307

#endif

#ifdef macos //needs to be checked
	# define W_KEY 18
	# define A_KEY 30
	# define S_KEY 31
	# define D_KEY 33
#endif

# define MOVEMENT_AMOUNT 0.1
# define ROTATION_AMOUNT 0.1
# define MINI_PLAYER_ICON_SIZE 5

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

typedef struct s_bresenham{
	int	dy;
	int	dx;
	int	p;
}	t_bresenham;

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
	int		map_width;
	int		map_height;
	//minimap
	int		mini_width_unit;
	int		mini_height_unit;
	//line
	t_bresenham *draw;
	//player
	//player position based on the coordinate of which grid box the player is in
	t_coord		player_map_position;
	//player position based on the coordinate of which grid box the player is in but with decimal (to show within the box)
	t_vector	player_position; 
	//player direction from the player position
	double		player_angle;
	t_vector	player_direction;
	// distance of the ray (accounting for its direction) to traverse one x and y unit
	double	delta_distance_x;
	double	delta_distance_y;
	// side length: the length of the ray to hit the x or y side of a wall
	double	side_length_x;
	double	side_length_y;
	double	final_side_length;
	
	t_vector	camera_plane;

	t_coord		step;
	t_vector	ray_direction;
}	t_main;

/* --------------------- > >> Prototypes << < --------------------- */

/* ----------------- ** gnl ** ------------------ */

char	*get_next_line(int fd);

/* -------------- ** temp parse ** -------------- */

int		get_y(char **map);
int		get_x(char *file);
char	**save_map(char **map, char *file, int x);

/* --------------- ** drawing ** ---------------- */

void	put_pixel(int x, int y, unsigned int color, t_main *s);
void	draw_rect(int width, int height, t_coord const *origin, t_main *s);
void	draw_circle(int radius, t_coord const *origin, t_main *s);

/* --------------- ** minimap ** ---------------- */

void	draw_minimap(t_main *s);
void	update_minimap(t_main *s);

/* ---------------- ** hooks ** ----------------- */

int		key_hooks(int keycode, t_main *s);
int		close_x(int keycode, t_main *s);

void	rotate_coor(double *x, double *y, double angle);

/* --------------- ** ray cast ** --------------- */

void	cast_rays(t_main *s);

/* ---------------- ** line ** ------------------ */

void	draw_line(t_coord start, t_coord end, t_main *s);


#endif