/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:58:07 by twagner           #+#    #+#             */
/*   Updated: 2021/12/21 17:05:27 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_get_sem_name(char type, int num, char *semname)
{
	int	len;

	if (!semname)
		return ;
	len = ft_nb_len(num) + 1;
	semname[0] = type;
	semname[len + 1] = 0;
	while (--len)
	{
		semname[len] = (num % 10) + 48;
		num /= 10;
	}
}

int	ft_is_sem_zero(const char *name)
{
	int	ret;

	ret = sem_unlink(name);
	if (ret == ERROR)
		return (0);
	return (1);
}
