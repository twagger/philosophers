/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:35:32 by twagner           #+#    #+#             */
/*   Updated: 2021/12/17 15:13:48 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_drop_forks(t_philo *phi)
{
	if (phi->has_forks)
	{
		pthread_mutex_unlock(&phi->left_fork);
		pthread_mutex_unlock(phi->right_fork);
		phi->has_forks = 0;
	}
}

static void	ft_force_wait_if_greedy(t_philo *phi)
{
	if (phi->prm->nb_philo % 2 == 1)
	{
		pthread_mutex_lock(&phi->m_last_meal);
		if (!(ft_get_timestamp() + phi->prm->timeto_eat \
			> phi->last_meal + phi->prm->timeto_die))
		{
			pthread_mutex_unlock(&phi->m_last_meal);
			ft_usleep(15);
		}
		else
			pthread_mutex_unlock(&phi->m_last_meal);
	}
}

void	ft_lock_forks(t_philo *phi)
{
	ft_force_wait_if_greedy(phi);
	if (phi->id == 1)
	{
		pthread_mutex_lock(&phi->left_fork);
		ft_say_status(phi, ST_FORK);
		pthread_mutex_lock(phi->right_fork);
		ft_say_status(phi, ST_FORK);
	}
	else
	{
		pthread_mutex_lock(phi->right_fork);
		ft_say_status(phi, ST_FORK);
		pthread_mutex_lock(&phi->left_fork);
		ft_say_status(phi, ST_FORK);
	}
	phi->has_forks = 1;
}
