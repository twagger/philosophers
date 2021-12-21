/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 22:37:46 by twagner           #+#    #+#             */
/*   Updated: 2021/12/21 20:35:32 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** NURSE ROUTINE
** Each time a philo start eating, a nurse is created to check on him
** in <time to die> milliseconds. If the philo's last meal is to old,
** the nurse updates the shared parameter to end the simulation.
*/

int	ft_create_nurse(t_philo *phi)
{
	pthread_t	nurse_id;

	if (pthread_create(&nurse_id, NULL, ft_nurse, (void *)phi) != 0)
		return (ERROR);
	if (pthread_detach(nurse_id) != 0)
		return (ERROR);
	return (0);
}

void	*ft_nurse(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	ft_usleep(phi->prm->timeto_die);
	pthread_mutex_lock(&phi->m_last_meal);
	pthread_mutex_lock(&phi->prm->m_nb_fed);
	if (ft_get_timestamp() >= phi->last_meal + phi->prm->timeto_die \
		&& phi->prm->nb_fed < phi->prm->nb_philo)
	{
		pthread_mutex_unlock(&phi->prm->m_nb_fed);
		pthread_mutex_unlock(&phi->m_last_meal);
		ft_say_status(phi, ST_DEAD);
		pthread_mutex_lock(&phi->prm->m_dead);
		phi->prm->dead = 1;
		pthread_mutex_unlock(&phi->prm->m_dead);
	}
	else
	{
		pthread_mutex_unlock(&phi->prm->m_nb_fed);
		pthread_mutex_unlock(&phi->m_last_meal);
	}
	return (NULL);
}

/*
** PHILO ROUTINE
** Displays the initial status, then launch a nurse thread to check
** if the philo is dead, then launch the actual loop of philo states
*/

static void	*ft_lonely_philo(t_philo *phi)
{
	ft_say_status(phi, ST_FORK);
	ft_usleep(phi->prm->timeto_die);
	ft_say_status(phi, ST_DEAD);
	return (NULL);
}

static int	ft_should_we_stop(t_philo *phi)
{
	pthread_mutex_lock(&phi->prm->m_dead);
	pthread_mutex_lock(&phi->prm->m_nb_fed);
	if (phi->prm->dead || phi->prm->nb_fed >= phi->prm->nb_philo)
	{
		pthread_mutex_unlock(&phi->prm->m_nb_fed);
		pthread_mutex_unlock(&phi->prm->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&phi->prm->m_nb_fed);
	pthread_mutex_unlock(&phi->prm->m_dead);
	return (0);
}

void	*ft_routine(void *philo)
{
	t_philo		*phi;

	phi = (t_philo *)philo;
	if (phi->prm->nb_philo == 1)
		return (ft_lonely_philo(phi));
	if (ft_create_nurse(phi) == ERROR)
		return (NULL);
	if (phi->id % 2)
		ft_usleep(30);
	while (1)
	{
		if (ft_philo_think(phi) == ERROR)
			break ;
		ft_philo_eat(phi);
		ft_philo_sleep(phi);
		if (ft_should_we_stop(phi))
			return (NULL);
	}
	return (NULL);
}
