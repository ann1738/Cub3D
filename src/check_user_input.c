/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:48:06 by Alia              #+#    #+#             */
/*   Updated: 2022/05/26 19:37:23 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	has_dot_cub(char *file_path)
{
	int	i;

	i = -1;
	while (file_path[++i])
	{
		if (file_path[i] == '.' && file_path[i + 1] == 'c' && \
		file_path[i + 2] == 'u' && file_path[i + 3] == 'b' && \
		!file_path[i + 4])
			return (true);
	}
	return (false);
}

bool	has_dot_xpm(char *file_path)
{
	int	i;

	i = -1;
	while (file_path[++i])
	{
		if (file_path[i] == '.' && file_path[i + 1] == 'x' && \
		file_path[i + 2] == 'p' && file_path[i + 3] == 'm' && \
		!file_path[i + 4])
			return (true);
	}
	return (false);
}

void	rgb_char_to_int(char *char_rgb, int int_rgb[3])
{
	int	i;

	int_rgb[0] = ft_atoi(&char_rgb[0]);
	i = -1;
	while (char_rgb[++i] != ',')
		;
	int_rgb[1] = ft_atoi(&char_rgb[++i]);
	while (char_rgb[++i] != ',')
		;
	int_rgb[2] = ft_atoi(&char_rgb[++i]);
}

static void	print_error_n_exit(int flag, char *argv1)
{
	if (flag == 1)
	{
		printf("%sError: wrog number of arguments%s\n", RED, RESET);
		printf("%s... <executable>  <file path> ...%s\n", YELLOW, RESET);
		exit(1);
	}
	else if (flag == 2)
	{
		printf("%sError: %s is not a file%s\n", RED, argv1, RESET);
		exit(1);
	}
	else if (flag == 3)
	{
		printf("%sError: %s can't be open%s\n", RED, argv1, RESET);
		exit(1);
	}
	else if (flag == 4)
	{
		printf("%sError: file must end with .cub%s\n", RED, RESET);
		exit(1);
	}
}

void	user_input_check(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		print_error_n_exit(1, argv[1]);
	fd = open(argv[1], O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		print_error_n_exit(2, argv[1]);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_error_n_exit(3, argv[1]);
	close(fd);
	if (has_dot_cub(argv[1]) == false)
		print_error_n_exit(4, argv[1]);
}
