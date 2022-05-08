/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alia <Alia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:42:21 by ann               #+#    #+#             */
/*   Updated: 2022/05/08 22:17:26 by Alia             ###   ########.fr       */
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

/* ----------------------- > >> Macros << < ----------------------- */

# define WINDOW_X 1680
# define WINDOW_Y 840

# define MINIMAP_X 420
# define MINIMAP_Y 210

# define BUFFER_SIZE 1

# define N "N"
# define S "S"

/* ----------------------- > >> Struct << < ----------------------- */

typedef struct s_coord
{
	int x;
	int y;
} t_coord;

typedef struct s_pars
{
	int		map_w;
	int		map_h;

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

	char	*f_color_rgb;
	int		f_color_rgb_int[3];
	char	*c_color_rgb;
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
	//
} t_main;

/* --------------------- > >> Prototypes << < --------------------- */

/* ----------- ** check user input ** ------------ */
void	user_input_check(int argc, char **argv);

/* ----------- ** save check map ** ------------- */
void	get_max_x_y(char *file_path, t_pars *p);
void	remove_nl(char *str);

/* ----------- ** full map save ** ------------- */
void	init_map_save(char *file_path, t_pars *p);

/* ------------- ** rgb to hex ** -------------- */
void	rgb_char_to_int(char *char_rgb, int int_rgb[3]);
void	rgb_to_hex(int rgb_int[3], char *hex);

/* ----------------- ** gnl ** ------------------ */
char	*get_next_line(int fd);

/* -------------- ** temp parse ** -------------- */
int		get_x(char *file);
char	**save_map(char **map, char *file, int x);

/* --------------- ** drawing ** ---------------- */
void	put_pixel(int x, int y, unsigned int color, t_main *s);
void	draw_rect(int width, int height, t_coord const *origin, t_main *s);

#endif