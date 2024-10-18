/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:42:43 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/07 14:36:18 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	creat_thread(t_philo *philos)
{
	int	i;

	i = 0;
	philos->data->pid = malloc(sizeof(int) * philos->data->nphilo);
	if (!philos->data->pid)
		exit(1);
	while (i < philos->data->nphilo)
	{
		philos->data->pid[i] = fork();
		if (philos->data->pid[i] == 0)
		{
			if (philos->id % 2 == 0)
				ft_usleep(philos->data->time_to_eat);
			routine(&philos[i]);
		}
		i++;
	}
}

void	init_philos(t_philo	*philos, t_data *data)
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
	creat_thread(philos);
}

void	init_data(char **av, t_data *data)
{
	data->nphilo = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->num_meal = ft_atoi(av[5]);
	else
		data->num_meal = -1;
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/die");
	data->fork = sem_open("/fork", O_CREAT, 0644, data->nphilo);
	if (data->fork == SEM_FAILED)
		printerror(data);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		printerror(data);
	data->die = sem_open("/die", O_CREAT, 0644, 1);
	if (data->die == SEM_FAILED)
		printerror(data);
}
