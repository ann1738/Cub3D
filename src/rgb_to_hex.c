/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 18:18:57 by Alia              #+#    #+#             */
/*   Updated: 2022/05/26 13:45:02 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
