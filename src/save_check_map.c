/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_check_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alia <Alia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:49:27 by Alia              #+#    #+#             */
/*   Updated: 2022/05/08 22:17:56 by Alia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_str_isrgb(char *str)
{
	int	i;
	int	comma_count;
	int	digit_count;

	i = 0;
	comma_count = 0;
	digit_count = 0;
	while (str[i])
	{
		if (str[i] == ',' && ft_isdigit(str[i + 1]))
		{
			digit_count = 0;
			comma_count++;
		}
		else if (!ft_isdigit(str[i]))
			return (false);
		if (digit_count > 3 || comma_count > 2)
			return (false);
		digit_count++;
		i++;
	}
	return (true);
}

void	remove_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = 0;
		i++;
	}
}

void	get_max_x_y(char *file_path, t_pars *p)
{
	int		i;
	int 	fd;
	char	*temp;

	fd = open(file_path, O_RDONLY);
	temp = get_next_line(fd);
	if (!temp)
		exit(1);
	i = 0;
	while (temp)
	{
		p->map_h++;
		i = ft_strlen(temp);
		if (i > p->map_w)
			p->map_w = i;
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
}

void	free_char_double_pointer(char **str)
{
	int i;
	
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	main(int argc, char **argv)
{
	t_pars	p;

	ft_bzero(&p, sizeof(t_pars));
	user_input_check(argc, argv);
	init_map_save(argv[1], &p);
	rgb_char_to_int(p.f_color_rgb, p.f_color_rgb_int);
	rgb_char_to_int(p.c_color_rgb, p.c_color_rgb_int);
	if (!p.n || !p.s || !p.w || !p.e || !p.f || !p.c || p.extra)
	{
		printf("%smap is shit%s\n", RED, RESET);
		free_char_double_pointer(p.full_file);
		exit(0);
	}
	if (ft_str_isrgb(p.f_color_rgb) == false || p.f_color_rgb_int[0] > 255 || p.f_color_rgb_int[1] > 255 || p.f_color_rgb_int[2] > 255)
	{
		printf("%sfloor is wrong%s\n", LIGHT_BLUE1, RESET);
		free_char_double_pointer(p.full_file);
		exit(0);
	}
	if (ft_str_isrgb(p.c_color_rgb) == false || p.c_color_rgb_int[0] > 255 || p.c_color_rgb_int[1] > 255 || p.c_color_rgb_int[2] > 255)
	{
		printf("%scelling is wrong%s\n", LIGHT_BLUE1, RESET);
		free_char_double_pointer(p.full_file);
		exit(0);
	}
	rgb_to_hex(p.f_color_rgb_int, p.f_color_hex);
	rgb_to_hex(p.c_color_rgb_int, p.c_color_hex);
	
	/* ----------------------- testing ---------------------- */
	printf("%syaaaay! no errors%s\n", GREEN1, RESET);

	printf("int: %d,%d,%d\n", p.f_color_rgb_int[0], p.f_color_rgb_int[1], p.f_color_rgb_int[2]);
	printf("char: %s\n", p.f_color_hex);

	printf("int: %d,%d,%d\n", p.c_color_rgb_int[0], p.c_color_rgb_int[1], p.c_color_rgb_int[2]);
	printf("char: %s\n", p.c_color_hex);

	
	// for (int i = 0; p.full_file[i]; i++)
	// 	printf("%s%s%s\n", PURPLE1, p.full_file[i], RESET);
	printf("%s*%s*%s\n", BLUE1, p.f_color_rgb, RESET);
	printf("%s*%s*%s\n", BLUE1, p.c_color_rgb, RESET);
	// printf("%s*%s*%s\n", GREEN1, p.s_texture, RESET);
	// printf("%s*%s*%s\n", GREEN1, p.n_texture, RESET);
	// printf("%s*%s*%s\n", GREEN1, p.w_texture, RESET);
	// printf("%s*%s*%s\n", GREEN1, p.e_texture, RESET);

}