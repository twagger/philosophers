/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:59:44 by twagner           #+#    #+#             */
/*   Updated: 2021/12/19 15:41:56 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_id_str(int id, char (*tmp)[10])
{
	int	len;

	memset((*tmp), 0, 10);
	len = ft_nb_len(id);
	(*tmp)[0] = '0';
	while (--len >= 0 && id != 0)
	{
		(*tmp)[len] = (id % 10) + 48;
		id /= 10;
	}
}

int	ft_create_philos(t_philo **philos, t_param *prm)
{
	int	i;

	if (!prm)
		return (ERROR);
	*philos = (t_philo *)malloc(sizeof(**philos) * prm->nb_philo);
	if (!*philos)
		return (ERROR);
	i = -1;
	while (++i < prm->nb_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].nb_eat = 0;
		(*philos)[i].last_meal = prm->start;
		(*philos)[i].prm = prm;
		(*philos)[i].has_forks = 0;
		pthread_mutex_init(&(*philos)[i].left_fork, NULL);
		pthread_mutex_init(&(*philos)[i].m_last_meal, NULL);
		(*philos)[i].right_fork = NULL;
		if (i != 0 && prm->nb_philo > 1)
			(*philos)[i].right_fork = &(*philos)[i - 1].left_fork;
	}
	if (prm->nb_philo > 1)
		(*philos)[0].right_fork = &(*philos)[prm->nb_philo - 1].left_fork;
	return (0);
}

void	ft_clear_philos(t_philo *philos, t_param *prm)
{
	int	i;

	if (philos)
	{
		pthread_mutex_lock(&prm->m_dead);
		i = -1;
		while (++i < prm->nb_philo)
		{
			pthread_mutex_destroy(&philos[i].left_fork);
			pthread_mutex_lock(&philos[i].m_last_meal);
			pthread_mutex_unlock(&philos[i].m_last_meal);
			pthread_mutex_destroy(&philos[i].m_last_meal);
		}
		pthread_mutex_unlock(&prm->m_dead);
		free(philos);
	}
}
