/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:48:06 by Alia              #+#    #+#             */
/*   Updated: 2022/05/09 12:44:12 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	has_dot_cub(char *file_path)
{
	int	i;

	i = -1;
	while (file_path[++i])
	{
		if (file_path[i] == '.')
		{
			if (file_path[i + 1] == 'c')
			{
				if (file_path[i + 2] == 'u')
				{
					if (file_path[i + 3] == 'b')
					{
						if (!file_path[i + 4])
							return (true);
					}
				}
			}
		}
	}
	return (false);
}

void	print_error_n_exit(int flag, char *argv1)
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
