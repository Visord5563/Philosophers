/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:54:29 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/06 11:46:28 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_post(philos->data->lock_die);
	// sem_post(philos->data->die);
	sem_close(philos->data->fork);
	sem_close(philos->data->lock_die);
	// sem_close(philos->data->lock_finish);
	// sem_close(philos->data->finish_eat);
	// sem_close(philos->data->die);
	sem_unlink("/hamid");
	sem_unlink("/die");
	sem_unlink("/look_die");
	sem_unlink("/finish");
	sem_unlink("/finish_eat");
	free(philos->data->pid);
	free(philos->data);
	free(philos);
	exit(0);
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

void waitfpid(t_philo *philos)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	j = 0;

	while (i < philos->data->nphilo)
	{
		waitpid(philos->data->pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			j = 0;
			while(j < philos->data->nphilo)
				kill(philos->data->pid[j++], SIGKILL);
		}
		i++;
	}
	exit_child(philos);

	destroy_free(philos);
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
	waitfpid(philos);
	return (0);
}
