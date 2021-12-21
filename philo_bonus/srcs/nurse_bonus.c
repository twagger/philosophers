/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nurse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:27:36 by twagner           #+#    #+#             */
/*   Updated: 2021/12/21 20:21:46 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
** DEATH NURSE ROUTINE
** Each time a philo start eating, a nurse is created to check on him
** in <time to die> milliseconds. If the philo's last meal is to old,
** the nurse updates the shared parameter to end the simulation.
*/

int	ft_create_death_nurse(t_philo *phi)
{
	pthread_t	nurse_id;

	if (pthread_create(&nurse_id, NULL, ft_death_nurse, (void *)phi) != 0)
		return (ERROR);
	if (pthread_detach(nurse_id) != 0)
		return (ERROR);
	return (0);
}

void	*ft_death_nurse(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	ft_usleep(phi->prm->timeto_die);
	sem_wait(phi->s_last_meal);
	if (ft_get_timestamp() >= phi->last_meal + phi->prm->timeto_die)
	{
		sem_post(phi->s_last_meal);
		ft_say_status(phi, ST_DEAD);
		sem_post(phi->prm->s_end);
	}
	else
		sem_post(phi->s_last_meal);
	return (NULL);
}

/*
** FED NURSE ROUTINE
** Loop on philos to check their number of meal.
** When a philo reach nb_eat number of meals, increment a variable.
** When the variable == nb philos > switch the end semaphore
*/

static int	ft_is_fed_nurse_necessary(t_param *prm)
{
	int	tte;
	int	tts;
	int	ttd;
	int	nb;

	tte = prm->timeto_eat;
	tts = prm->timeto_sleep;
	ttd = prm->timeto_die;
	nb = prm->nb_philo;
	if (tte + tts > ttd)
		return (0);
	if (nb % 2 == 1 && tte * 2 >= ttd)
		return (0);
	return (1);
}

int	ft_create_fed_nurse(t_param *prm)
{
	pthread_t	nurse_id;

	if (prm->nb_philo == 1 \
		|| prm->nb_eat == -1 \
		|| !ft_is_fed_nurse_necessary(prm))
		return (0);
	if (pthread_create(&nurse_id, NULL, ft_fed_nurse, (void *)prm) != 0)
		return (ERROR);
	if (pthread_detach(nurse_id) != 0)
		return (ERROR);
	return (0);
}

void	*ft_fed_nurse(void *param)
{
	int		i;
	t_param	*prm;

	prm = (t_param *)param;
	i = -1;
	while (++i < prm->nb_philo)
		sem_wait(prm->s_fed);
	sem_post(prm->s_end);
	return (NULL);
}
