/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:48:38 by twagner           #+#    #+#             */
/*   Updated: 2021/12/18 11:37:26 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_error(t_param *prm, t_philo *philos)
{
	if (prm && philos)
		ft_clear_philos(philos, prm);
	else if (prm)
		ft_clear_param(prm);
	ft_putstr_fd("Error\n", 2);
	return (1);
}

static int	ft_parser(int ac, char **av, t_param **prm)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (ERROR);
	i = 0;
	while (++i < ac)
	{
		if (ft_strlen(av[i]) == 0)
			return (ERROR);
		if (ft_strlen(av[i]) == 1 && !(av[i][0] >= 48 && av[i][0] <= 57))
			return (ERROR);
		if (ft_atoi(av[i]) < 0)
			return (ERROR);
		if (i == 1 && ft_atoi(av[i]) == 0)
			return (ERROR);
	}
	if (ft_init_param(ac, av, prm) == ERROR)
		return (ERROR);
	return (0);
}

int	main(int ac, char **av)
{
	int			i;
	t_param		*prm;
	t_philo		*philos;

	philos = NULL;
	prm = NULL;
	if (ft_parser(ac, av, &prm) == -1 || ft_create_philos(&philos, prm) == -1)
		return (ft_print_error(prm, philos));
	i = -1;
	while (++i < prm->nb_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL, \
			ft_routine, &philos[i]) != 0)
			return (ft_print_error(prm, philos));
	}
	i = -1;
	while (++i < prm->nb_philo)
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			return (ft_print_error(prm, philos));
	ft_usleep(prm->timeto_die + 1);
	ft_clear_philos(philos, prm);
	ft_clear_param(prm);
	return (0);
}
