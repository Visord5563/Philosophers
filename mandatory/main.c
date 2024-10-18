/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:54:29 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/06 11:12:55 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long long			r;
	int					s;

	s = 1;
	r = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (r * 10 > 2147483640 || (r * 10 == 2147483640
				&& ((*str > '7' && s == 1) || (*str > '8' && s == -1))))
			return (-1);
		r = r * 10 + (*str - 48);
		str++;
	}
	return (r * s);
}

void	destroy_free(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philos->data->lock_die);
	pthread_mutex_destroy(&philos->data->lock_finish);
	while (i < philos->data->nphilo)
	{
		pthread_mutex_destroy(&philos->data->fork[i]);
		i++;
	}
	free(philos->data->fork);
	free(philos->data);
	free(philos);
}

int	parsing(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				return (0);
			j++;
		}
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philos;

	if (ac > 6 || ac < 5)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (parsing(av) == 0)
		return (printf("wrong\n"), free(data), 1);
	if (init_data(av, data))
		return (free(data), 1);
	philos = malloc(sizeof(t_philo) * data->nphilo);
	if (!philos)
		return (free(data), 1);
	if (init_philos(philos, data))
		return (free(data), 1);
	destroy_free(philos);
	return (0);
}
