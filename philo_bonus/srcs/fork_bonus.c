/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:35:32 by twagner           #+#    #+#             */
/*   Updated: 2021/12/21 09:46:30 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_drop_forks(t_philo *phi)
{
	sem_post(phi->prm->s_fork);
	sem_post(phi->prm->s_fork);
}

static void	ft_force_wait_if_greedy(t_philo *phi)
{
	if (phi->prm->nb_philo % 2 == 1)
	{
		if (!(ft_get_timestamp() + phi->prm->timeto_eat \
			> phi->last_meal + phi->prm->timeto_die))
			ft_usleep(phi->prm->timeto_eat / 100);
	}
}

void	ft_lock_forks(t_philo *phi)
{
	ft_force_wait_if_greedy(phi);
	sem_wait(phi->prm->s_fork);
	ft_say_status(phi, ST_FORK);
	sem_wait(phi->prm->s_fork);
	ft_say_status(phi, ST_FORK);
}
