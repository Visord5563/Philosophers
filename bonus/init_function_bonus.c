/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:42:43 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/05 15:15:16 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	creat_thread(t_philo *philos)
{
	int	i;

	i = 0;
	if(philos->data->num_meal != -1)
	{
		pthread_create(&philos->data->thread, NULL, check_finished, philos);
		pthread_detach(philos->data->thread);
	}
	philos->data->pid = malloc(sizeof(int) * philos->data->nphilo);
	sem_wait(philos->data->die);
	while (i < philos->data->nphilo)
	{
		philos->data->pid[i] = fork();
		if (philos->data->pid[i] == 0)
		{
			routine(&philos[i]);
		}
		i++;
	}
	sem_wait(philos->data->die);
	exit_child(philos);
	i = -1;
	while (++i < philos->data->nphilo)
		waitpid(i, NULL, 0);
	return (0);
}

int	init_philos(t_philo	*philos, t_data *data)
{
	int	i;

	i = 0;

	while (i < data->nphilo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].count = 0;
		philos[i].data->start = get_time();
		philos[i].times_last_eat = get_time();
		i++;
	}
	if (creat_thread(philos))
		return (1);
	return (0);
}

int	init_data(char **av, t_data *data)
{
	data->nphilo = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->num_meal = ft_atoi(av[5]);
	else
		data->num_meal = -1;
	sem_unlink("/hamid");
	data->fork = sem_open("/hamid", O_CREAT , 0644,	 data->nphilo);
	if(data->fork == SEM_FAILED)
	{
		sem_close(data->fork);
		sem_unlink("/hamid");
		return (1);
	}
	sem_unlink("/finish_eat");
	data->finish_eat = sem_open("/finish_eat", O_CREAT , 0644,	 0);
	if(data->finish_eat == SEM_FAILED)
	{
		sem_close(data->finish_eat);
		sem_unlink("/finish_eat");
		return (1);
	}
	sem_unlink("/lock_die");
	data->lock_die = sem_open("/lock_die", O_CREAT , 0644,	 1);
	if(data->lock_die == SEM_FAILED)
	{
		sem_close(data->lock_die);
		sem_unlink("/die");
		return (1);
	}
	sem_unlink("/lock_finish");
	data->lock_finish = sem_open("/lock_finish", O_CREAT , 0644,	 1);
	if(data->lock_finish == SEM_FAILED)
	{
		sem_close(data->lock_finish);
		sem_unlink("/lock_finish");
		return (1);
	}
	sem_unlink("/die");
	data->die = sem_open("/die", O_CREAT , 0644,	 1);
	if(data->die == SEM_FAILED)
	{
		sem_close(data->die);
		sem_unlink("/die");
		return (1);
	}
	return (0);
}
