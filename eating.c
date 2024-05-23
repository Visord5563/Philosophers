/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:49:57 by saharchi          #+#    #+#             */
/*   Updated: 2024/05/23 13:51:48 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philos)
{
	long long	time;

	take_fork(philos);
	pthread_mutex_lock(&philos->data->look_die);
	philos->times_last_eat = get_time();
	philos->count++;
	if (philos->data->die)
	{
		pthread_mutex_unlock(&philos->data->look_die);
		pthread_mutex_unlock(&philos->data->fork[philos->r_fork]);
		pthread_mutex_unlock(&philos->data->fork[philos->l_fork]);
		return (1);
	}
	time = get_time() - philos->data->start;
	printf("%lld %d %s\n", time, philos->id, EATING);
	pthread_mutex_unlock(&philos->data->look_die);
	ft_usleep(philos->data->time_to_eat);
	pthread_mutex_unlock(&philos->data->fork[philos->r_fork]);
	pthread_mutex_unlock(&philos->data->fork[philos->l_fork]);
	return (0);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void	ft_write(char *str, t_philo *philos)
{
	long long	time;

	pthread_mutex_lock(&philos->data->look_die);
	time = get_time() - philos->data->start;
	if (!philos->data->die)
		printf("%lld %d %s\n", time, philos->id, str);
	pthread_mutex_unlock(&philos->data->look_die);
}

void	ft_sleep(t_philo *philos)
{
	ft_write(SLEEPING, philos);
	ft_usleep(philos->data->time_to_sleep);
	ft_write(THINKING, philos);
}
