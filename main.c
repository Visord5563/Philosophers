
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:54:29 by saharchi          #+#    #+#             */
/*   Updated: 2024/05/16 13:17:16 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_die(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->look_die);
	if (get_time() - philos->times_last_eat > philos->data->time_to_die)
	{
		printf("%lld %d %s\n", get_time() - philos->data->start, philos->id, DIED);
		philos->data->die = 1;
		pthread_mutex_unlock(&philos->data->look_die);
		return 1;
	}
	pthread_mutex_unlock(&philos->data->look_die);
	return (0);
}

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

void take_fork(t_philo *philos)
{
	philos->r_fork = philos->id - 1;
	philos->l_fork = philos->id % philos->data->nphilo;
	pthread_mutex_lock(&philos->data->fork[philos->r_fork]);
	ft_write(TAKE_FORKS, philos);
	if (philos->data->nphilo == 1)
	{
		pthread_mutex_unlock(&philos->data->fork[philos->r_fork]);
		ft_usleep(philos->data->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(&philos->data->fork[philos->l_fork]);
	ft_write(TAKE_FORKS, philos);
}

int	eat(t_philo *philos)
{

	take_fork(philos);
	pthread_mutex_lock(&philos->data->look_die);
	philos->times_last_eat = get_time();
	philos->count++;
	if(philos->data->die)
	{
		pthread_mutex_unlock(&philos->data->look_die);
		pthread_mutex_unlock(&philos->data->fork[philos->r_fork]);
		pthread_mutex_unlock(&philos->data->fork[philos->l_fork]);
		return 1;
	}
	printf("%lld %d %s\n", get_time() - philos->data->start, philos->id, EATING);
	pthread_mutex_unlock(&philos->data->look_die);
	ft_usleep(philos->data->time_to_eat);
	pthread_mutex_unlock(&philos->data->fork[philos->r_fork]);
	pthread_mutex_unlock(&philos->data->fork[philos->l_fork]);
	return 0;
}

void ft_sleep(t_philo *philos)
{
	ft_write(SLEEPING, philos);
	ft_usleep(philos->data->time_to_sleep);
	ft_write(THINKING, philos);
}

int check_finished(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->look_die);
	pthread_mutex_lock(&philos->data->look_finish);
	if (philos->data->finish_eat == philos->data->nphilo)
	{
		philos->data->die = 1;
		pthread_mutex_unlock(&philos->data->look_die);
		pthread_mutex_unlock(&philos->data->look_finish);
		return (1);
	}
	pthread_mutex_unlock(&philos->data->look_die);
	pthread_mutex_unlock(&philos->data->look_finish);
	return (0);
}

void destroy_free(t_philo *philos)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&philos->data->look_die);
	pthread_mutex_destroy(&philos->data->look_finish);
	while(i < philos->data->nphilo)
	{
		pthread_mutex_destroy(&philos->data->fork[i]);
		i++;
	}
	free(philos->data->fork);
	free(philos);
}

void *monitoring(void *arg)
{
	t_philo	*philos;
	
	philos = (t_philo *)arg;

	while(!philos->data->die)
	{
		if (check_die(philos) || check_finished(philos))	
			break ;
	}
	return NULL;
}

void ft_write(char *str, t_philo *philos)
{
	pthread_mutex_lock(&philos->data->look_die);
	if (!philos->data->die)
		printf("%lld %d %s\n", get_time() - philos->data->start, philos->id, str);
	pthread_mutex_unlock(&philos->data->look_die);
}

void *routine(void *arg)
{
    t_philo	*philos;
	
	philos = (t_philo *)arg;
	if (philos->id % 2 == 0)
		usleep(philos->data->time_to_eat);
	while(1)
	{
		if (eat(philos))
			return NULL;
		if (philos->count == philos->data->num_meal)
		{
			pthread_mutex_lock(&philos->data->look_finish);
			philos->data->finish_eat++;
			pthread_mutex_unlock(&philos->data->look_finish);
		}
		ft_sleep(philos);
	}
    return NULL;
}

long long get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_usleep(long long time)
{
	long long start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}


int 	parsing(char **av)
{
	int i;
	int j;
	
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
			{
				return (0);
			}
			j++;
		}
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

void init_philos(t_philo	*philos, t_data *data)
{
	int i;
	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nphilo);
	while(i < data->nphilo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].count = 0;
		philos[i].eat = 0;
		philos[i].data->start = get_time();
		philos[i].times_last_eat = get_time();
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	i = 0;
	while(i < data->nphilo)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	pthread_create(&philos->data->t, NULL, monitoring, philos);
	i = 0;
	while(i < data->nphilo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_detach(philos->data->t);
}

void init_data(char **av, t_data *data)
{
	pthread_mutex_init(&data->look_die, NULL);
	pthread_mutex_init(&data->look_finish, NULL);
	data->nphilo = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_die = ft_atoi(av[2]);
	data->die = 0;
	data->finish_eat = 0;
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->flag == 1)
		data->num_meal = ft_atoi(av[5]);
	else
		data->num_meal = -1;
}

// void f()
// {
// 	system("leaks philo");
// }

int main(int ac, char **av)
{

	t_data *data;
	t_philo	*philos;

	// atexit(f);
	data = malloc(sizeof(t_data));
	if (ac > 6 || ac < 5 ||  ft_atoi(av[1]) > 200)	
		return (1);
	if (ac == 6)
	{
		data->flag = 1;
	}
	else 
		data->flag = 0;
	if (parsing(av) == 0)
	{
		write(1, "wrong\n", 6);
		return (0);
	}
	init_data(av, data);
	philos = malloc(sizeof(t_philo) * data->nphilo);
	init_philos(philos, data);
	destroy_free(philos);
	return (0);
}
