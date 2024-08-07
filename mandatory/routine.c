/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:45:29 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/07 14:14:58 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->id % 2 == 0)
		ft_usleep(50, philos);
	while (1)
	{
		eat(philos);
		pthread_mutex_lock(&philos->data->lock_die);
		if (philos->data->die)
		{
			pthread_mutex_unlock(&philos->data->lock_die);
			return (NULL);
		}
		pthread_mutex_unlock(&philos->data->lock_die);
		if (philos->count == philos->data->num_meal)
		{
			pthread_mutex_lock(&philos->data->lock_finish);
			philos->data->finish_eat++;
			pthread_mutex_unlock(&philos->data->lock_finish);
		}
		ft_sleep(philos);
	}
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (!philos->data->die)
	{
		i = 0;
		while (i < philos->data->nphilo)
		{
			if (check_die(&philos[i]) || check_finished(&philos[i]))
				break ;
			i++;
		}
	}
	return (NULL);
}

int	check_finished(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->lock_die);
	pthread_mutex_lock(&philos->data->lock_finish);
	if (philos->data->finish_eat == philos->data->nphilo)
	{
		philos->data->die = 1;
		pthread_mutex_unlock(&philos->data->lock_die);
		pthread_mutex_unlock(&philos->data->lock_finish);
		return (1);
	}
	pthread_mutex_unlock(&philos->data->lock_die);
	pthread_mutex_unlock(&philos->data->lock_finish);
	return (0);
}

int	check_die(t_philo *philos)
{
	long long	time;

	pthread_mutex_lock(&philos->data->lock_die);
	if (get_time() - philos->times_last_eat > philos->data->time_to_die)
	{
		time = get_time() - philos->data->start;
		if (!philos->data->die)
			printf("%lld %d %s\n", time, philos->id, DIED);
		philos->data->die = 1;
		pthread_mutex_unlock(&philos->data->lock_die);
		return (1);
	}
	pthread_mutex_unlock(&philos->data->lock_die);
	return (0);
}

void	take_fork(t_philo *philos)
{
	philos->r_fork = philos->id - 1;
	philos->l_fork = philos->id % philos->data->nphilo;
	pthread_mutex_lock(&philos->data->fork[philos->l_fork]);
	ft_write(TAKE_FORKS, philos);
	if (philos->data->nphilo == 1)
	{
		ft_usleep(philos->data->time_to_die + 1, philos);
		pthread_mutex_unlock(&philos->data->fork[philos->l_fork]);
		return ;
	}
	pthread_mutex_lock(&philos->data->fork[philos->r_fork]);
	ft_write(TAKE_FORKS, philos);
}
