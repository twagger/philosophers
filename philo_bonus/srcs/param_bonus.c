/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:59:28 by twagner           #+#    #+#             */
/*   Updated: 2021/12/21 19:15:01 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_destroy_prm_sems(t_param *prm)
{
	if (prm)
	{
		sem_close(prm->s_end);
		sem_close(prm->s_talk);
		sem_close(prm->s_fork);
		sem_close(prm->s_fed);
		sem_unlink("talk");
		sem_unlink("end");
		sem_unlink("fork");
		sem_unlink("fed");
	}
}

int	ft_init_param(int ac, char **av, t_param **prm)
{
	*prm = (t_param *)malloc(sizeof(**prm));
	if (!(*prm))
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
	sem_unlink("fork");
	sem_unlink("talk");
	sem_unlink("end");
	sem_unlink("fed");
	(*prm)->s_fork = sem_open("fork", O_CREAT | O_EXCL, 0666, (*prm)->nb_philo);
	(*prm)->s_talk = sem_open("talk", O_CREAT | O_EXCL, 0666, 1);
	(*prm)->s_end = sem_open("end", O_CREAT | O_EXCL, 0666, 0);
	(*prm)->s_fed = sem_open("fed", O_CREAT | O_EXCL, 0666, 0);
	return (0);
}
