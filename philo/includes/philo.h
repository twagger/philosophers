/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:50:46 by twagner           #+#    #+#             */
/*   Updated: 2021/12/21 20:35:20 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** LIBRARIES
*/

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdint.h>
# include <stddef.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

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
	u_int64_t		timeto_die;
	u_int64_t		timeto_eat;
	u_int64_t		timeto_sleep;
	int				nb_eat;
	int				nb_fed;
	u_int64_t		start;
	int				dead;
	pthread_mutex_t	m_talk;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_nb_fed;
}					t_param;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	m_last_meal;
	int				has_forks;
	u_int64_t		last_meal;
	int				nb_eat;
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
void		ft_clear_param(t_param *prm);
int			ft_create_philos(t_philo **philos, t_param *prm);
void		ft_clear_philos(t_philo *philos, t_param *prm);

void		*ft_routine(void *philo);
void		*ft_nurse(void *philo);
int			ft_create_nurse(t_philo *phi);

char		*ft_get_status(int code);
void		ft_say_status(t_philo *phi, int status);
int			ft_philo_think(t_philo *phi);
void		ft_philo_sleep(t_philo *phi);
void		ft_philo_eat(t_philo *phi);

void		ft_lock_forks(t_philo *phi);
void		ft_drop_forks(t_philo *phi);

#endif
