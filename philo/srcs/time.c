/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:13:23 by twagner           #+#    #+#             */
/*   Updated: 2021/12/17 14:44:17 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_timestamp_str(u_int64_t begin, char (*tmp)[10])
{
	u_int64_t	ts;
	int			len;

	ts = ft_get_timestamp() - begin;
	len = ft_nb_len(ts);
	(*tmp)[0] = '0';
	(*tmp)[len] = ' ';
	(*tmp)[len + 1] = 0;
	while (--len >= 0 && ts != 0)
	{
		(*tmp)[len] = (ts % 10) + 48;
		ts /= 10;
	}
}

u_int64_t	ft_get_timestamp(void)
{
	static struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	ft_usleep(u_int64_t time_in_ms)
{
	u_int64_t	start_time;

	start_time = ft_get_timestamp();
	while ((ft_get_timestamp() - start_time) < time_in_ms)
		usleep((time_in_ms * 1000) / 100);
}
