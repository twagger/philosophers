/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:28:10 by twagner           #+#    #+#             */
/*   Updated: 2021/12/21 20:25:18 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_philo_think(t_philo *phi)
{
	ft_say_status(phi, ST_THINKING);
	ft_lock_forks(phi);
	sem_wait(phi->s_last_meal);
	phi->last_meal = ft_get_timestamp();
	sem_post(phi->s_last_meal);
	ft_say_status(phi, ST_EATING);
	if (ft_create_death_nurse(phi) == ERROR)
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
			sem_post(phi->prm->s_fed);
	}
	ft_drop_forks(phi);
}

char	*ft_get_status(int code)
{
	if (code == ST_SLEEPING)
		return (" is sleeping\n");
	if (code == ST_EATING)
		return (" is eating\n");
	if (code == ST_THINKING)
		return (" is thinking\n");
	if (code == ST_DEAD)
		return (" died\n");
	if (code == ST_FORK)
		return (" has taken a fork\n");
	return ("");
}

void	ft_say_status(t_philo *phi, int status)
{
	char		text[29];
	char		tmp[10];

	sem_wait(phi->prm->s_talk);
	sem_wait(phi->s_dead);
	if (!phi->dead)
	{
		text[0] = 0;
		ft_get_timestamp_str(phi->prm->start, &tmp);
		ft_strcat(&text, tmp);
		ft_get_id_str(phi->id, &tmp);
		ft_strcat(&text, tmp);
		if (status == ST_DEAD)
			phi->dead = 1;
		ft_strcat(&text, ft_get_status(status));
		ft_putstr_fd(text, 1);
		if (!phi->dead)
			sem_post(phi->prm->s_talk);
	}
	else
		sem_post(phi->prm->s_talk);
	sem_post(phi->s_dead);
}
