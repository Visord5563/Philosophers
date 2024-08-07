/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:45:29 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/07 14:39:33 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (pthread_create(&philos->t, NULL, monitoring, philos) != 0)
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

void	printerror(t_data *data)
{
	if (data->fork == SEM_FAILED)
	{
		sem_close(data->fork);
		sem_unlink("/fork");
	}
	else if (data->die == SEM_FAILED)
	{
		sem_close(data->fork);
		sem_unlink("/fork");
		sem_close(data->print);
		sem_unlink("/print");
		sem_close(data->die);
		sem_unlink("/die");
	}
	else if (data->print == SEM_FAILED)
	{
		sem_close(data->fork);
		sem_unlink("/fork");
		sem_close(data->print);
		sem_unlink("/print");
	}
	printf("Error: sem_open failed\n");
	free(data);
	exit(1);
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
			exit(1);
		}
		sem_post(philos->data->die);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	take_fork(t_philo *philos)
{
	sem_wait(philos->data->fork);
	ft_write(TAKE_FORKS, philos);
	sem_wait(philos->data->fork);
	ft_write(TAKE_FORKS, philos);
}
