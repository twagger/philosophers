/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:50:46 by twagner           #+#    #+#             */
/*   Updated: 2021/12/21 20:32:49 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/*
** LIBRARIES
*/

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdint.h>
# include <stddef.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

/*
** GLOBAL PARAMS
*/

enum e_errors
{
	ERROR = -1
};

enum e_status
{
	ST_SLEEPING,
	ST_EATING,
	ST_THINKING,
	ST_DEAD,
	ST_FORK
};

/*
** DATA STRUCTURES
*/

typedef struct s_param
{
	int				nb_philo;
	int				child_pid[200];
	u_int64_t		timeto_die;
	u_int64_t		timeto_eat;
	u_int64_t		timeto_sleep;
	int				nb_eat;
	u_int64_t		start;
	sem_t			*s_fork;
	sem_t			*s_talk;
	sem_t			*s_fed;
	sem_t			*s_end;
}					t_param;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_t		nurse_id;
	int				nb_eat;
	int				dead;
	u_int64_t		last_meal;
	sem_t			*s_last_meal;
	sem_t			*s_dead;
	t_param			*prm;
}					t_philo;

/*
** Utils
*/

size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);
void		ft_putnbr_fd(int n, int fd);
u_int64_t	ft_get_timestamp(void);
void		ft_usleep(u_int64_t time_in_ms);
int			ft_nb_len(int n);
void		ft_get_timestamp_str(u_int64_t begin, char (*tmp)[10]);
void		ft_get_id_str(int id, char (*tmp)[10]);
void		ft_strcat(char (*dest)[29], const char *src);

/* 
** Main functions
*/

int			ft_init_param(int ac, char **av, t_param **prm);
int			ft_create_philos(t_philo **philos, t_param *prm);

int			ft_routine(t_philo *phi);
void		*ft_death_nurse(void *philo);
int			ft_create_death_nurse(t_philo *phi);
int			ft_create_fed_nurse(t_param *prm);
void		*ft_fed_nurse(void *param);

char		*ft_get_status(int code);
void		ft_say_status(t_philo *phi, int status);
int			ft_philo_think(t_philo *phi);
void		ft_philo_sleep(t_philo *phi);
void		ft_philo_eat(t_philo *phi);

void		ft_lock_forks(t_philo *phi);
void		ft_drop_forks(t_philo *phi);

void		ft_get_sem_name(char type, int num, char *semname);
int			ft_is_sem_zero(const char *name);

void		ft_destroy_philos_sems(t_philo *philos);
void		ft_destroy_prm_sems(t_param *prm);

#endif
