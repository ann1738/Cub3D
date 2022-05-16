/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 18:18:57 by Alia              #+#    #+#             */
/*   Updated: 2022/05/16 13:01:20 by aalsuwai         ###   ########.fr       */
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
