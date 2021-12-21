/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 22:17:33 by twagner           #+#    #+#             */
/*   Updated: 2021/12/18 10:55:27 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		++i;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_atoi(const char *str)
{
	double	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == '+')
		++str;
	if (*str < 48 && *str > 57)
		return (-1);
	while (*str >= 48 && *str <= 57)
	{
		result = (result * 10) + (*str - 48);
		++str;
	}
	if (*str)
		return (-1);
	if (result > LONG_MAX)
		return (-1);
	return ((int)result);
}

int	ft_nb_len(int n)
{
	int	len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		++len;
	}
	return (len);
}

void	ft_strcat(char (*dest)[29], const char *src)
{
	int	i;

	i = 0;
	while ((*dest)[i])
		++i;
	while (*src)
	{
		(*dest)[i] = *src;
		++i;
		++src;
	}
	(*dest)[i] = 0;
}
