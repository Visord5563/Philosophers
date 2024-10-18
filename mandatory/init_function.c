/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:42:43 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/07 14:12:08 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	creat_thread(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_create(&philos->data->t, NULL, monitoring, philos);
	while (i < philos->data->nphilo)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
			return (printf("Error creating thread thread\n"), 1);
		i++;
	}
	i = 0;
	while (i < philos->data->nphilo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_detach(philos->data->t);
	return (0);
}

int	init_philos(t_philo	*philos, t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nphilo);
	while (i < data->nphilo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].count = 0;
		philos[i].data->start = get_time();
		philos[i].times_last_eat = get_time();
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (printf("Error initializing mutex for fork\n"), 1);
		i++;
	}
	if (creat_thread(philos))
		return (1);
	return (0);
}

int	init_data(char **av, t_data *data)
{
	if (pthread_mutex_init(&data->lock_die, NULL) != 0)
		return (printf("Error initializing mutex for look_die\n"), 1);
	if (pthread_mutex_init(&data->lock_finish, NULL) != 0)
		return (printf("Error initializing mutex for look_finish\n"), 1);
	data->nphilo = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_die = ft_atoi(av[2]);
	data->die = 0;
	data->finish_eat = 0;
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->num_meal = ft_atoi(av[5]);
	else
		data->num_meal = -1;
	return (0);
}
