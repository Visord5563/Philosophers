/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:53:48 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/07 14:12:31 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_data
{
	pthread_t		t;
	int				die;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock_die;
	pthread_mutex_t	lock_finish;
	int				num_meal;
	int				finish_eat;
	long long		time_to_die;
	long long		time_to_eat;
	long long		start;
	long long		time_to_sleep;
	int				nphilo;
}	t_data;

typedef struct s_philo
{
	long long		times_last_eat;
	int				r_fork;
	int				l_fork;
	int				count;
	pthread_t		thread;
	int				id;
	struct s_data	*data;
}	t_philo;

int			ft_atoi(const char *str);
int			parsing(char **av);
void		*routine(void *arg);
long long	get_time(void);
void		ft_usleep(long long time, t_philo *philos);
void		ft_write(char *str, t_philo *philos);
int			check_finished(t_philo *philos);
int			init_data(char **av, t_data *data);
void		destroy_free(t_philo *philos);
void		*monitoring(void *arg);
void		eat(t_philo *philos);
void		ft_sleep(t_philo *philos);
int			creat_thread(t_philo *philos);
int			init_philos(t_philo	*philos, t_data *data);
int			check_die(t_philo *philos);
void		take_fork(t_philo *philos);

#endif