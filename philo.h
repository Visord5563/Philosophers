/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:53:48 by saharchi          #+#    #+#             */
/*   Updated: 2024/05/20 16:03:17 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_data
{
	int c;
	pthread_t		t;
	int				die;
	pthread_mutex_t	*fork;
	pthread_mutex_t	look_eting;
	pthread_mutex_t	look_die;
	pthread_mutex_t	look_sleep;
	pthread_mutex_t	look_write;
	time_t			num_meal;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			start;
	time_t			time_to_sleep;
	int				flag;
	int				nphilo;
} t_data;

typedef struct s_philo
{
	int				eat;
	int				r_fork;
	int				l_fork;
	int 			count;
	pthread_t		thread;
	time_t			new_time_to_die;
	time_t			times_last_eat;
	int				id;
	struct s_data 	*data;
} t_philo;
 
int		ft_atoi(const char *str);
int 	parsing(char **av);
void	*retune(void *arg);
time_t	get_time(void);
void ft_usleep(long long time, t_philo *philos);
void ft_write(char *str, t_philo *philos);
// int check_finished(t_philo *philos, t_data *data);
void init_data(char **av, t_data *data);

#endif