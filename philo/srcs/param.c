/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:59:28 by twagner           #+#    #+#             */
/*   Updated: 2021/12/17 15:10:22 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_param(int ac, char **av, t_param **prm)
{
	*prm = (t_param *)malloc(sizeof(**prm));
	if (!*prm)
		return (ERROR);
	(*prm)->nb_philo = ft_atoi(av[1]);
	(*prm)->timeto_die = ft_atoi(av[2]);
	(*prm)->timeto_eat = ft_atoi(av[3]);
	(*prm)->timeto_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*prm)->nb_eat = ft_atoi(av[5]);
	else
		(*prm)->nb_eat = -1;
	(*prm)->start = ft_get_timestamp();
	(*prm)->dead = 0;
	(*prm)->nb_fed = 0;
	pthread_mutex_init(&(*prm)->m_talk, NULL);
	pthread_mutex_init(&(*prm)->m_dead, NULL);
	pthread_mutex_init(&(*prm)->m_nb_fed, NULL);
	return (0);
}

void	ft_clear_param(t_param *prm)
{
	if (prm)
	{
		pthread_mutex_lock(&prm->m_talk);
		pthread_mutex_unlock(&prm->m_talk);
		pthread_mutex_destroy(&prm->m_talk);
		pthread_mutex_lock(&prm->m_dead);
		pthread_mutex_unlock(&prm->m_dead);
		pthread_mutex_destroy(&prm->m_dead);
		pthread_mutex_lock(&prm->m_nb_fed);
		pthread_mutex_unlock(&prm->m_nb_fed);
		pthread_mutex_destroy(&prm->m_nb_fed);
		free(prm);
	}
}
