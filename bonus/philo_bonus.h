/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:53:48 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/07 14:57:03 by saharchi         ###   ########.fr       */
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
	sem_t			*die;
	sem_t			*fork;
	int				*pid;
	sem_t			*print;
	int				num_meal;
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
void		init_data(char **av, t_data *data);
void		destroy_free(t_philo *philos);
void		*monitoring(void *arg);
void		eat(t_philo *philos);
void		ft_sleep(t_philo *philos);
void		creat_thread(t_philo *philos);
void		init_philos(t_philo	*philos, t_data *data);
void		take_fork(t_philo *philos);
int			ft_strcmp(const char *s1, const char *s2);
void		printerror(t_data *data);

#endif