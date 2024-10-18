/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:54:29 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/07 14:29:35 by saharchi         ###   ########.fr       */
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
	sem_close(philos->data->fork);
	sem_close(philos->data->print);
	sem_close(philos->data->die);
	sem_unlink("/fork");
	sem_unlink("/die");
	sem_unlink("/print");
	free(philos->data->pid);
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

void	waitfpid(t_philo *philos)
{
	int	i;
	int	status;

	i = 0;
	while (i < philos->data->nphilo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status))
		{
			i = 0;
			while (i < philos->data->nphilo)
				kill(philos->data->pid[i++], SIGKILL);
			break ;
		}
		i++;
	}
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
		exit(1);
	if (parsing(av) == 0)
		return (printf("wrong\n"), free(data), 1);
	init_data(av, data);
	philos = malloc(sizeof(t_philo) * data->nphilo);
	if (!philos)
	{
		free(data);
		exit(1);
	}
	init_philos(philos, data);
	waitfpid(philos);
	return (0);
}
