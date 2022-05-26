/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:52:46 by ann               #+#    #+#             */
/*   Updated: 2022/05/26 16:50:53 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	draw_line_lower(t_coord *start, t_coord *end, \
t_coord *temp, t_main *s)
{
	s->draw->p = (2 * abs(s->draw->dy) - abs(s->draw->dx));
	while (start->x <= end->x)
	{
		if (s->draw->dy < 0 && !check_outside_minimap(start->x, \
		start->y - (2 * (start->y - temp->y))))
			put_pixel(start->x, start->y - (2 * (start->y - temp->y)), \
			RAY_COLOR, s);
		else if (s->draw->dx < 0 && !check_outside_minimap(start->x - \
		(2 * (start->x - temp->x)), start->y))
			put_pixel(start->x - (2 * (start->x - temp->x)), start->y, \
			RAY_COLOR, s);
		else if (!check_outside_minimap(start->x, start->y))
			put_pixel(start->x, start->y, RAY_COLOR, s);
		(start->x)++;
		if (s->draw->p < 0)
			s->draw->p = s->draw->p + (2 * abs(s->draw->dy));
		else
		{
			s->draw->p = s->draw->p + (2 * abs(s->draw->dy)) - \
			(2 * abs(s->draw->dx));
			(start->y)++;
		}
	}
}

static void	draw_line_higher(t_coord *start, t_coord *end, \
t_coord *temp, t_main *s)
{
	s->draw->p = (2 * abs(s->draw->dx)) - abs(s->draw->dy);
	while (start->y <= end->y)
	{
		if (s->draw->dy < 0 && !check_outside_minimap(start->x, \
		start->y - (2 * (start->y - temp->y))))
			put_pixel(start->x, start->y - (2 * (start->y - temp->y)), \
			RAY_COLOR, s);
		else if (s->draw->dx < 0 && !check_outside_minimap(start->x - \
		(2 * (start->x - temp->x)), start->y))
			put_pixel(start->x - (2 * (start->x - temp->x)), start->y, \
			RAY_COLOR, s);
		else if (!check_outside_minimap(start->x, start->y))
			put_pixel(start->x, start->y, RAY_COLOR, s);
		(start->y)++;
		if (s->draw->p < 0)
			s->draw->p = s->draw->p + (2 * abs(s->draw->dx));
		else
		{
			s->draw->p = s->draw->p + (2 * abs(s->draw->dx)) - \
			(2 * abs(s->draw->dy));
			(start->x)++;
		}
	}
}

static void	swap_and_abs(t_coord *start, t_coord *end, t_main *s)
{
	ft_swap(&(start->y), &(end->y));
	ft_swap(&(start->x), &(end->x));
	s->draw->dy = abs(s->draw->dy);
	s->draw->dx = abs(s->draw->dx);
}

/* This function draws a line from start coordinates to the end coordinates */
/* based on Bresenham's line-drawing algorithm */
void	draw_line(t_coord start, t_coord end, t_main *s)
{
	t_bresenham		b;
	t_coord			temp;

	s->draw = &b;
	b.p = 0;
	temp.x = start.x;
	temp.y = start.y;
	b.dy = end.y - start.y;
	b.dx = end.x - start.x;
	if (b.dy < 0 && b.dx < 0)
		swap_and_abs(&start, &end, s);
	else if (b.dy < 0)
		end.y = end.y + (2 * (start.y - end.y));
	else if (b.dx < 0)
		end.x = end.x + (2 * (start.x - end.x));
	if (abs(b.dy) <= abs(b.dx))
		draw_line_lower(&start, &end, &temp, s);
	else
		draw_line_higher(&start, &end, &temp, s);
}
