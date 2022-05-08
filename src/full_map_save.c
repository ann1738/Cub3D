/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_map_save.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alia <Alia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:49:10 by Alia              #+#    #+#             */
/*   Updated: 2022/05/08 18:16:44 by Alia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	save_texture_no_so(char *map_line, t_pars *p, int *i)
{
	if (map_line[*i] == 'N' && map_line[*i + 1] == 'O' && \
	(map_line[*i + 2] == ' ' || map_line[*i + 2] == '\t'))
	{
		*i += 2;
		while (ft_isspace(map_line[*i]))
			(*i)++;
		p->n_texture = &map_line[*i];
		p->n = true;
		return (0);
	}
	else if (map_line[*i] == 'S' && map_line[*i + 1] == 'O' && \
	(map_line[*i + 2] == ' ' || map_line[*i + 2] == '\t'))
	{
		*i += 2;
		while (ft_isspace(map_line[*i]))
			(*i)++;
		p->s_texture = &map_line[*i];
		p->s = true;
		return (0);
	}
	return (1);
}

static int	save_texture_we_ea(char *map_line, t_pars *p, int *i)
{
	if (map_line[*i] == 'W' && map_line[*i + 1] == 'E' && \
	(map_line[*i + 2] == ' ' || map_line[*i + 2] == '\t'))
	{
		*i += 2;
		while (ft_isspace(map_line[*i]))
			(*i)++;
		p->w_texture = &map_line[*i];
		p->w = true;
		return (0);
	}
	else if (map_line[*i] == 'E' && map_line[*i + 1] == 'A' && \
	(map_line[*i + 2] == ' ' || map_line[*i + 2] == '\t'))
	{
		*i += 2;
		while (ft_isspace(map_line[*i]))
			(*i)++;
		p->e_texture = &map_line[*i];
		p->e = true;
		return (0);
	}
	return (1);
}

static int	save_texture_f_c_extra(char *map_line, t_pars *p, int *i)
{
	if (map_line[*i] == 'F' && \
	(map_line[*i + 1] == ' ' || map_line[*i + 1] == '\t'))
	{
		*i += 1;
		while (ft_isspace(map_line[*i]))
			(*i)++;
		p->f_color_rgb = &map_line[*i];
		p->f = true;
		return (0);
	}
	else if (map_line[*i] == 'C' && \
	(map_line[*i + 1] == ' ' || map_line[*i + 1] == '\t'))
	{
		*i += 1;
		while (ft_isspace(map_line[*i]))
			(*i)++;
		p->c_color_rgb = &map_line[*i];
		p->c = true;
		return (0);
	}
	else
		p->extra = true;
	return (1);
}

static void	check_save_texture(char *map_line, t_pars *p)
{
	int	i;
	
	i = 0;
	while (map_line[i])
	{
		if (p->n && p->s && p->w && p->e && p->f && p->c)
			return ;
		if (!ft_isspace(map_line[i]))
		{
			if (!save_texture_no_so(map_line, p, &i))
				return ;
			else if (!save_texture_we_ea(map_line, p, &i))
				return ;
			else if (!save_texture_f_c_extra(map_line, p, &i))
				return ;
		}
		i++;
	}
}

void	init_map_save(char *file_path, t_pars *p)
{
	int		i;
	int 	fd;

	get_max_x_y(file_path, p);
	p->full_file = ft_calloc((p->map_h + 1), sizeof(char **));
	fd = open(file_path, O_RDONLY);
	i = 0;
	while (i < p->map_h)
	{
		p->full_file[i] = get_next_line(fd);
		remove_nl(p->full_file[i]);
		check_save_texture(p->full_file[i], p);
		i++;
	}
}
