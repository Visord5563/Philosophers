/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:45:29 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/06 11:46:24 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->id % 2 == 0)
		usleep(philos->data->time_to_eat);
	if(pthread_create(&philos->t, NULL, monitoring, philos) != 0)
	{
		printf("Error creating thread\n");
		exit(1);
	}
	pthread_detach(philos->t);
	while (1)
	{
		eat(philos);
		if (philos->count == philos->data->num_meal)
			break ;
		ft_sleep(philos);
	}
	exit(0);
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

	while (1)
	{
		if (philos->count == philos->data->num_meal)
			return (NULL);
		if (get_time() - philos->times_last_eat > philos->data->time_to_die)
		{
			ft_write(DIED, philos);
			exit(1);
		}
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
