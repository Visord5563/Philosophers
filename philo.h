/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:53:48 by saharchi          #+#    #+#             */
/*   Updated: 2024/05/16 17:51:50 by saharchi         ###   ########.fr       */
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

typedef struct s_data
{
	int				die;
	pthread_mutex_t	*fork;
	pthread_mutex_t	look_eting;
	pthread_mutex_t	look_die;
	pthread_mutex_t	look_sleep;
	pthread_mutex_t	look_write;
	time_t			num_meal;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				flag;
	int				nphilo;
} t_data;

typedef struct s_philo
{
	int				r_fork;
	int				l_fork;
	int 			count;
	pthread_t		thread;
	time_t			times_last_eat;
	time_t			start;
	int				id;
	struct s_data 	*data;
} t_philo;
 
int		ft_atoi(const char *str);
int 	parsing(char **av, t_data *data);
void	*retune(void *arg);
time_t	get_time(void);
void ft_usleep(long long time);
void ft_write(t_philo *philos, int i);
int check_die(t_philo *philos, t_data *data);
int check_finished(t_philo *philos, t_data *data);

#endif