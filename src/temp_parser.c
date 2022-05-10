/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 20:25:26 by ann               #+#    #+#             */
/*   Updated: 2022/05/10 16:41:35 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**save_map(char **map, char *file, int y)
{
	int	i;
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("%sError: invalid file%s\n", RED, RESET);
		exit(1);
	}
	map = (char **)malloc((y + 1) * sizeof(char *));
	if (!map)
		exit(1);
	i = 0;
	while (i < y)
		map[i++] = get_next_line(fd);
	map[i] = 0;
	close(fd);
	return (map);
}

int	get_y(char *file)
{
	int		y;
	int		fd;
	char	*line;

	fd = open(file, O_DIRECTORY);
	if (fd > 0)
	{
		printf("%sError: invalid file%s\n", RED, RESET);
		close(fd);
		exit(1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("%sError: invalid file%s\n", RED, RESET);
		exit(1);
	}
	line = get_next_line(fd);
	y = 0;
	while (line)
	{	
		y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (y);
}

// int	main(int argc, char **argv)
// {
// 	int		x;
// 	int		y;
// 	char	**map;

// 	x = get_x(argv[1]);
// 	printf("%d\n", x);
// 	map = save_map(map, argv[1], x);
// 	for (x = 0; map[x]; x++)
// 	{
// 		for (y = 0; map[x][y]; y++)
// 			printf("(%d, %d) ", x, y);
// 		printf("\n");
// 	}
// 	for (x = 0; map[x]; x++)
// 	{
// 		for (y = 0; map[x][y]; y++)
// 		{
// 			if (map[x][y] == 'E')
// 			{
// 				printf("%c = (%d, %d)\n", map[x][y], x, y);
// 				break ;
// 			}
// 		}
// 	}
// }