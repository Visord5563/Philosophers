/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:45:29 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/05 15:15:00 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->id % 2 == 0)
		usleep(philos->data->time_to_eat);
	pthread_create(&philos->t, NULL, monitoring, philos);
	pthread_detach(philos->t);
	while (1)
	{
		eat(philos);
		if (philos->count == philos->data->num_meal)
		{
			sem_post(philos->data->finish_eat);
		}
		ft_sleep(philos);
	}
	return (NULL);
}

void exit_child(t_philo *philos)
{
	int i;

	i = 0;
	while(i < philos->data->nphilo)
	{
		kill(philos->data->pid[i], SIGKILL);
		waitpid(philos->data->pid[i], NULL, 0);
		i++;
  	}
	destroy_free(philos);
}

void	*monitoring(void *arg)
{
	t_philo	*philos;
	philos = (t_philo *)arg;
	long long	time;

	while (1)
	{
		if (get_time() - philos->times_last_eat > philos->data->time_to_die)
		{
			sem_wait(philos->data->lock_die);
			time = get_time() - philos->data->start;
			printf("%lld %d %s\n", time, philos->id, DIED);
			sem_post(philos->data->die);
			return (NULL);
		}
	}
	return (NULL);
}

void	*check_finished(void *arg)
{
	t_philo	*philos;
	int		i;
	
	i = -1;
	philos = (t_philo *)arg;
	while(++i < philos->data->nphilo)
	{
		sem_wait(philos->data->finish_eat);
	}
	sem_post(philos->data->lock_die);
	return (NULL);
}


void	take_fork(t_philo *philos)
{
	sem_wait(philos->data->fork);
	ft_write(TAKE_FORKS, philos);
	if (philos->data->nphilo == 1)
	{
		ft_usleep(philos->data->time_to_die * 2);
		sem_post(philos->data->fork);
	}
	sem_wait(philos->data->fork);
	ft_write(TAKE_FORKS, philos);
}
