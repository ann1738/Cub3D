/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:31:26 by aalsuwai          #+#    #+#             */
/*   Updated: 2022/05/26 19:52:36 by aalsuwai         ###   ########.fr       */
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

int	ft_open_n_free(t_pars *p, char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		printf("%sError: %s can't be open%s\n", RED, file_path, RESET);
		free_char_double_pointer(p->full_file);
		exit(1);
	}
	return (fd);
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
		close(fd);
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

void	*ft_calloc_p(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		printf("%sError: fatal error%s\n", RED2, RESET);
		exit(1);
	}
	return (ptr);
}
