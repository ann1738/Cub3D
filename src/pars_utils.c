/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:31:26 by aalsuwai          #+#    #+#             */
/*   Updated: 2022/05/09 13:54:13 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_char_double_pointer(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	remove_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = 0;
		i++;
	}
}

void	get_max_x_y(char *file_path, t_pars *p)
{
	int		i;
	int		fd;
	char	*temp;

	fd = open(file_path, O_RDONLY);
	temp = get_next_line(fd);
	if (!temp)
	{
		close(fd); //close before exit
		exit(1);
	}
	i = 0;
	while (temp)
	{
		p->file_h++;
		i = ft_strlen(temp);
		if (i > p->file_w)
			p->file_w = i;
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
}
