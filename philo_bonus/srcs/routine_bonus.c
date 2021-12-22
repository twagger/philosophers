/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 22:37:46 by twagner           #+#    #+#             */
/*   Updated: 2021/12/22 23:33:45 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

/*
** PHILO ROUTINE
** Displays the initial status, then launch a nurse thread to check
** if the philo is dead, then launch the actual loop of philo states
*/

static int	ft_lonely_philo(t_philo *phi)
{
	ft_say_status(phi, ST_THINKING);
	ft_say_status(phi, ST_FORK);
	ft_usleep(phi->prm->timeto_die);
	ft_say_status(phi, ST_DEAD);
	sem_post(phi->prm->s_end);
	return (0);
}

int	ft_routine(t_philo *phi)
{
	if (phi->prm->nb_philo == 1)
		return (ft_lonely_philo(phi));
	if (ft_create_death_nurse(phi) == ERROR)
		return (1);
	if (phi->id % 2)
		ft_usleep(30);
	while (1)
	{
		if (ft_philo_think(phi) == ERROR)
			break ;
		ft_philo_eat(phi);
		ft_philo_sleep(phi);
	}
	return (0);
}
