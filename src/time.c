/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:29:44 by ann               #+#    #+#             */
/*   Updated: 2022/05/12 15:41:32 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* when frames per second (fps) is to be included just involve it in the */
/* movement formula */

void	fps(t_main *s)
{
	s->frame2 = clock();
	s->fps = (double)(s->frame2 - s->frame1) / CLOCKS_PER_SEC;
	s->frame1 = s->frame2;
}
