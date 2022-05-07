/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 20:25:26 by ann               #+#    #+#             */
/*   Updated: 2022/04/30 14:24:57 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**save_map(char **map, char *file, int x)
{
	int	i;
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("%sError: invalid file%s\n", RED, RESET);
		exit(1);
	}
	map = (char **)malloc((x + 1) * sizeof(char *));
	if (!map)
		exit(1);
	i = 0;
	while (i < x)
		map[i++] = get_next_line(fd);
	map[i] = 0;
	printf("x = %d\n", x);
	close(fd);
	return (map);
}

int	get_y(char **map)
{
	int count = -1;
	while (map[++count]);
	return (count);
}

int	get_x(char *file)
{
	int		x;
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
	x = 0;
	while (line[x] && line[x] != '\n')
		x++;
	free(line);
	close(fd);
	return (x);
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