/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:53:48 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/06 11:37:26 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_data
{
	pthread_t		thread;
	sem_t				*die;
	sem_t			*fork;
	int 			*pid;
	sem_t		*lock_die;
	sem_t		*lock_finish;
	int				num_meal;
	sem_t			*finish_eat;
	long long		time_to_die;
	long long		time_to_eat;
	long long		start;
	long long		time_to_sleep;
	int				nphilo;
}	t_data;

typedef struct s_philo
{
	pthread_t		t;
	long long		times_last_eat;
	int				count;
	int				id;
	struct s_data	*data;
}	t_philo;

int			ft_atoi(const char *str);
int			parsing(char **av);
void		*routine(void *arg);
long long	get_time(void);
void		ft_usleep(long long time);
void		ft_write(char *str, t_philo *philos);
void		*check_finished(void *arg);
int			init_data(char **av, t_data *data);
void		destroy_free(t_philo *philos);
void		*monitoring(void *arg);
void			eat(t_philo *philos);
void		ft_sleep(t_philo *philos);
int			creat_thread(t_philo *philos);
int			init_philos(t_philo	*philos, t_data *data);
int			check_die(t_philo *philos);
void		take_fork(t_philo *philos);
void		exit_child(t_philo *philos);

#endif