/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:48:38 by twagner           #+#    #+#             */
/*   Updated: 2021/12/21 19:00:07 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
** DESTROY SEMS
** Close and Unlink all semaphores at the end of the program
*/

static void	ft_destroy_sems(t_philo *philos, t_param *prm)
{
	ft_destroy_prm_sems(prm);
	ft_destroy_philos_sems(philos);
}

/*
** PARSER
** Check if the parameters are ok
*/

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

/*
** LAUNCH PROCESSES
** Launch every philo as a subprocess of the main. After the philo process
** ends, waits for the eventual last nurse to die, then close every semaphore
** used and free all malloc'ed duplicated addresses
** 
*/

static int	ft_launch_processes(int id, t_param *prm, t_philo *philos)
{
	static int	i = -1;
	pid_t		pid;

	pid = fork();
	if (pid == ERROR)
		return (ERROR);
	if (pid == 0)
	{
		ft_routine(&philos[id]);
		exit (0);
	}
	else
		prm->child_pid[++i] = pid;
	return (0);
}

/*
** LAUNCH AND WAIT
** Launch processes and wait for the end of all of them
*/

static int	ft_launch_and_wait(t_param *prm, t_philo *philos)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < prm->nb_philo)
	{
		ret = ft_launch_processes(i, prm, philos);
		if (ret == ERROR)
			return (1);
	}
	ret = ft_create_fed_nurse(prm);
	if (ret == ERROR)
		return (1);
	sem_wait(prm->s_end);
	i = -1;
	while (++i < prm->nb_philo)
		kill(prm->child_pid[i], SIGTERM);
	return (0);
}

/*
** MAIN
** Create a global param for processes to communicate,
** then create a structure to store each philo's infos,
** then start them and wait
*/

int	main(int ac, char **av)
{
	int		ret;
	t_param	*prm;
	t_philo	*philos;

	ret = 1;
	philos = NULL;
	prm = NULL;
	if (!ft_parser(ac, av, &prm) && !ft_create_philos(&philos, prm))
		ret = ft_launch_and_wait(prm, philos);
	ft_destroy_sems(philos, prm);
	if (ret == 1)
		ft_putstr_fd("Error\n", 2);
	free(philos);
	free(prm);
	return (ret);
}
