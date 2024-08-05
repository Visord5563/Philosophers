/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:49:57 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/05 12:42:05 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *philos)
{
	long long	time;

	take_fork(philos);
	philos->times_last_eat = get_time();
	philos->count++;
	time = get_time() - philos->data->start;
	printf("%lld %d %s\n", time, philos->id, EATING);
	ft_usleep(philos->data->time_to_eat);
	sem_post(philos->data->fork);
	sem_post(philos->data->fork);
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

	// sem_wait(philos->data->look_die);
	time = get_time() - philos->data->start;
	printf("%lld %d %s\n", time, philos->id, str);
	// sem_post(philos->data->look_die);
}

void	ft_sleep(t_philo *philos)
{
	ft_write(SLEEPING, philos);
	ft_usleep(philos->data->time_to_sleep);
	ft_write(THINKING, philos);
}
