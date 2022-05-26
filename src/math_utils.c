/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:45:41 by ann               #+#    #+#             */
/*   Updated: 2022/05/26 17:22:31 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180.0));
}

double	rad_to_deg(double rad)
{
	return (rad * (180.0 / M_PI));
}

void	rotate_coor(double *x, double *y, double angle)
{
	double	temp_x;

	temp_x = *x;
	*x = (*x * cos(angle)) - (*y * sin(angle));
	*y = (temp_x * sin(angle)) + (*y * cos(angle));
}
