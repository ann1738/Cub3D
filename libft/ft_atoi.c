/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 00:54:29 by anasr             #+#    #+#             */
/*   Updated: 2022/04/28 13:02:31 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == '+' || str[i] == '-') && str[i++] == '-')
			sign *= -1;
	if (ft_strlen(str) > 19 && sign == 1)
		return (-1);
	else if (ft_strlen(str) > 20 && sign == -1)
		return (0);
	while (ft_isdigit(str[i]) == 1)
	{
		if (result >= LONG_MAX / 10 && str[i] > '7' && sign == 1)
			return (-1);
		if (result >= LONG_MAX / 10 && str[i] > '8' && sign == -1)
			return (0);
		result = 10 * result + (str[i] - 48);
		i++;
	}
	return (result * sign);
}
