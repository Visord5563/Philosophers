/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:45:29 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/06 16:07:08 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if(pthread_create(&philos->t, NULL, monitoring, philos) != 0)
	{
		printf("Error creating thread\n");
		exit(1);
	}
	// pthread_detach(philos->t);
	while (1)
	{
		eat(philos);
		if (philos->count == philos->data->num_meal)
			break ;
		ft_sleep(philos);
	}
	pthread_join(philos->t, NULL);
	exit(0);
}


void	*monitoring(void *arg)
{
	t_philo	*philos;
	philos = (t_philo *)arg;

	while (1)
	{
		sem_wait(philos->data->die);
		if (philos->count == philos->data->num_meal)
		{
			sem_post(philos->data->die);
			return (NULL);
		}
		if (get_time() - philos->times_last_eat > philos->data->time_to_die)
		{
			ft_write(DIED, philos);
			sem_post(philos->data->die);
			exit(1);
		}
		sem_post(philos->data->die);
	}
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
