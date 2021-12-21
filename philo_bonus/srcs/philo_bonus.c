/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:59:44 by twagner           #+#    #+#             */
/*   Updated: 2021/12/21 19:06:09 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_destroy_philos_sems(t_philo *philos)
{
	int		i;
	char	sem_name[20];

	if (philos)
	{
		memset((void *)sem_name, 0, 20);
		i = -1;
		while (++i < philos[0].prm->nb_philo)
		{
			sem_close(philos[i].s_last_meal);
			ft_get_sem_name('m', i, (char *)sem_name);
			sem_unlink(sem_name);
			sem_close(philos[i].s_dead);
			ft_get_sem_name('d', i, (char *)sem_name);
			sem_unlink(sem_name);
		}
	}
}

int	ft_create_philos(t_philo **philos, t_param *prm)
{
	int		i;
	char	sem_name[20];

	if (!prm)
		return (ERROR);
	memset((void *)sem_name, 0, 20);
	*philos = (t_philo *)malloc(sizeof(**philos) * prm->nb_philo);
	if (!(*philos))
		return (ERROR);
	i = -1;
	while (++i < prm->nb_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].nb_eat = 0;
		(*philos)[i].prm = prm;
		(*philos)[i].last_meal = prm->start;
		ft_get_sem_name('m', i, (char *)sem_name);
		sem_unlink(sem_name);
		(*philos)[i].s_last_meal = sem_open(sem_name, O_CREAT, 0666, 1);
		(*philos)[i].dead = 0;
		ft_get_sem_name('d', i, (char *)sem_name);
		sem_unlink(sem_name);
		(*philos)[i].s_dead = sem_open(sem_name, O_CREAT, 0666, 1);
	}
	return (0);
}
