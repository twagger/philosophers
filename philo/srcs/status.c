/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:28:10 by twagner           #+#    #+#             */
/*   Updated: 2021/12/21 20:34:53 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_think(t_philo *phi)
{
	ft_say_status(phi, ST_THINKING);
	ft_lock_forks(phi);
	pthread_mutex_lock(&phi->m_last_meal);
	phi->last_meal = ft_get_timestamp();
	pthread_mutex_unlock(&phi->m_last_meal);
	ft_say_status(phi, ST_EATING);
	if (ft_create_nurse(phi) == ERROR)
		return (ERROR);
	return (0);
}

void	ft_philo_sleep(t_philo *phi)
{
	ft_say_status(phi, ST_SLEEPING);
	ft_usleep(phi->prm->timeto_sleep);
}

void	ft_philo_eat(t_philo *phi)
{
	ft_usleep(phi->prm->timeto_eat);
	if (phi->prm->nb_eat != -1)
	{
		if (++(phi->nb_eat) == phi->prm->nb_eat \
			|| phi->prm->nb_eat == 0)
		{
			pthread_mutex_lock(&phi->prm->m_nb_fed);
			++(phi->prm->nb_fed);
			pthread_mutex_unlock(&phi->prm->m_nb_fed);
		}
	}
	ft_drop_forks(phi);
}

char	*ft_get_status(int code)
{
	if (code == 0)
		return (" is sleeping\n");
	if (code == 1)
		return (" is eating\n");
	if (code == 2)
		return (" is thinking\n");
	if (code == 3)
		return (" died\n");
	if (code == 4)
		return (" has taken a fork\n");
	return ("");
}

void	ft_say_status(t_philo *phi, int status)
{
	char		text[29];
	char		tmp[10];
	static int	dead = 0;

	pthread_mutex_lock(&phi->prm->m_talk);
	if (!dead)
	{
		text[0] = 0;
		ft_get_timestamp_str(phi->prm->start, &tmp);
		ft_strcat(&text, tmp);
		ft_get_id_str(phi->id, &tmp);
		ft_strcat(&text, tmp);
		if (status == ST_DEAD)
			dead = 1;
		ft_strcat(&text, ft_get_status(status));
		ft_putstr_fd(text, 1);
		pthread_mutex_unlock(&phi->prm->m_talk);
	}
	else
		pthread_mutex_unlock(&phi->prm->m_talk);
}
