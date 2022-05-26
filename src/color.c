/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:33:14 by anasr             #+#    #+#             */
/*   Updated: 2022/05/26 16:24:12 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function to convert rgb to unsigned int */
unsigned int	rgb_to_uint(int transp, int red, int green, int blue)
{
	return (transp << 24 | red << 16 | green << 8 | blue);
}

/* function to convert unsigned int to rgb */
void	uint_to_rgb(unsigned int uint_color, t_color *rgb_color)
{
	rgb_color->blue = (uint_color & 0x000000ff) & 255;
	rgb_color->green = ((uint_color & 0x0000ff00) >> 8) & 255;
	rgb_color->red = ((uint_color & 0x00ff0000) >> 16) & 255;
}

/* function that mixes the given color with fog color with an intensity */
void	add_fog(double intensity, t_color fog_color, t_color *color)
{
	if (intensity >= 0 && intensity <= 1)
	{
		color->red = ((char)(color->red * (1.0 - intensity)) + \
		(char)(fog_color.red * intensity)) & 255;
		color->green = ((char)(color->green * (1.0 - intensity)) + \
		(char)(fog_color.green * intensity)) & 255;
		color->blue = ((char)(color->blue * (1.0 - intensity)) + \
		(char)(fog_color.blue * intensity)) & 255;
	}
	else
		write(2, "Invalid intensity for the function add_fog\n", 43);
}

/* function that mixes the given color with fog color with an intensity */
/* but takes the color in the form of an unsigned int */
unsigned int	add_fog_uint(double intensity, t_color *fog_color, \
unsigned int color)
{
	int		r;
	int		g;
	int		b;
	double	intensity_inverse;

	intensity_inverse = 1.0 - intensity;
	r = ((char)((((color & 0x00ff0000) >> 16) & 255) * intensity_inverse) \
	+ (char)(fog_color->red * intensity)) & 255;
	g = ((char)((((color & 0x0000ff00) >> 8) & 255) * intensity_inverse) \
	+ (char)(fog_color->green * intensity)) & 255;
	b = ((char)((color & 0x000000ff) * intensity_inverse) \
	+ (char)(fog_color->blue * intensity)) & 255;
	return (r << 16 | g << 8 | b);
}

/* function to assign rgb colors in the color struct */
void	assign_rgb_color(int red, int green, int blue, t_color *color)
{
	color->blue = blue & 255;
	color->green = green & 255;
	color->red = red & 255;
}
