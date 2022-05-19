/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_n_look.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:29:39 by anasr             #+#    #+#             */
/*   Updated: 2022/05/19 16:30:04 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	jump_n_crouch(t_main *s)
{
	static int i = 0;

	if (s->jump && s->jump_now)
	{
		usleep(2500);
		i += 50;
		s->position_z = i;
		redraw_window(s);
		if (s->position_z >= 400)
			s->jump_now = false;
		return (0);
	}
	else if (s->jump && !s->jump_now)
	{
		if (s->position_z >= 400 && write(2, "HEYEYEYE\n", 9))
			usleep(10000);
		i -= 50;
		s->position_z = i;
		usleep(2500);
		redraw_window(s);
		if (s->position_z <= 0)
		{
			s->jump_now = false;
			s->jump = false;
		}
		return (0);
	}
	if (s->crouch && s->crouch_now)
	{
		s->position_z = -400;
		redraw_window(s);
		s->crouch_now = false;
		return (0);
	}
	else if (s->crouch && !s->crouch_now)
	{
		s->position_z = 0;
		usleep(300000);
		redraw_window(s);
		s->crouch_now = false;
		s->crouch = false;
		return (0);
	}
	return (0);
}

int	activate_jump(int button, int x, int y, t_main *s)
{
	(void)(x);
	(void)(y);
	if (button == 3)
	{
		s->jump = true;
		s->jump_now = true;
	}
	return (0);
}
