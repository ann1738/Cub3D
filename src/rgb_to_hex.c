/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alia <Alia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 18:18:57 by Alia              #+#    #+#             */
/*   Updated: 2022/05/08 22:17:20 by Alia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_rgb_part(char *rgb_color, int starting_pos)
{
	int		i;
	int		count;
	char	*temp;

	count = starting_pos;
	while (rgb_color[count] && rgb_color[count] != ',')
		count++;
	temp = (char *)ft_calloc((count + 1), sizeof(char));
	if (!temp)
		exit (1);
	i = 0;
	while (rgb_color[starting_pos] && rgb_color[starting_pos] != ',')
	{
		temp[i] = rgb_color[starting_pos];
		starting_pos++;
		i++;
	}
	return (temp);
}

void	rgb_char_to_int(char *char_rgb, int int_rgb[3])
{
	int		i;
	char	*rgb_part;

	rgb_part = get_rgb_part(char_rgb, 0);
	int_rgb[0] = ft_atoi(rgb_part);
	free(rgb_part);
	i = 0;
	while (char_rgb[i] != ',')
		i++;
	i++;
	rgb_part = get_rgb_part(char_rgb, i);
	int_rgb[1] = ft_atoi(rgb_part);
	free(rgb_part);
	while (char_rgb[i] != ',')
		i++;
	i++;
	rgb_part = get_rgb_part(char_rgb, i);
	int_rgb[2] = ft_atoi(rgb_part);
	free(rgb_part);
}

void	make_hex(unsigned int n, char str[7], int i)
{
	int	temp_num;

	if (n > 15)
	{
		temp_num = n / 16;
		if (temp_num >= 0 && temp_num <= 9)
			str[i] = temp_num + 48;
		else if (temp_num >= 10 && temp_num <= 15)
			str[i] = temp_num + 87;
		i++;
		temp_num = n % 16;
		if (temp_num >= 0 && temp_num <= 9)
			str[i] = temp_num + 48;
		else if (temp_num >= 10 && temp_num <= 15)
			str[i] = temp_num + 87;
		i++;
	}
	else if (n >= 0 && n <= 9)
	{
		str[i] = '0';
		i++;
		str[i] = n + 48;
	}
	else if (n >= 10 && n <= 15)
	{
		str[i] = '0';
		i++;
		str[i] = n + 87;
	}
}

void	rgb_to_hex(int rgb_int[3], char hex[7])
{
	make_hex(rgb_int[0], hex, 0);
	make_hex(rgb_int[1], hex, 2);
	make_hex(rgb_int[2], hex, 4);
	hex[6] = 0;
	printf("%shex: %s%s\n", YELLOW1, hex, RESET);
}