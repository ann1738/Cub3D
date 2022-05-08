/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 12:11:38 by ann               #+#    #+#             */
/*   Updated: 2022/05/08 17:42:21 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	if_newline(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}

int	s_len(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*join_with_temp(char *old_ret, char *temp)
{
	int		len;
	int		ret_i;
	int		temp_i;
	char	*new_ret;

	len = s_len(old_ret) + 1;
	new_ret = malloc((len + 1) * sizeof(char));
	if (!new_ret)
		return (0);
	ret_i = 0;
	while (old_ret && old_ret[ret_i])
	{
		new_ret[ret_i] = old_ret[ret_i];
		ret_i++;
	}
	temp_i = 0;
	while (temp && temp[temp_i])
	{
		new_ret[ret_i] = temp[temp_i];
		temp_i++;
		ret_i++;
	}
	new_ret[ret_i] = 0;
	free(old_ret);
	return (new_ret);
}

char	*get_next_line(int fd)
{
	char	*ret;
	char	temp[2];
	int		check;

	ret = 0;
	temp[0] = 0;
	temp[1] = 0;
	check = 1;
	while (check)
	{
		check = read(fd, temp, 1);
		if (check == -1)
			return (0);
		else if (!check)
			return (ret);
		ret = join_with_temp(ret, temp);
		if (if_newline(ret))
			return (ret);
	}
	return (ret);
}
