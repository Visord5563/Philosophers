
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

int check_die(t_philo *philos, t_data *data)
{
	int i;

	i = 0;
	while(i < data->nphilo)
	{
		if(get_time() - philos[i].times_last_eat > data->time_to_die)
		{
			printf("here1 %ld %ld\n",  philos[i].times_last_eat, data->time_to_die);
			return (1);
		}
		i++;
	}
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
	pthread_mutex_lock(&philos->data->fork[philos->l_fork]);
	ft_write(TAKE_FORKS, philos);
}

void	eat(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->look_eting);
	ft_write(EATING, philos);
	philos->times_last_eat = get_time();
	printf("ana id %d rani hna db%ld\n",philos->id, philos->times_last_eat);
	philos->count++;
	philos->data->c++;
	ft_usleep(philos->data->time_to_eat, philos);
	pthread_mutex_unlock(&philos->data->look_eting);
	pthread_mutex_unlock(&philos->data->fork[philos->r_fork]);
	pthread_mutex_unlock(&philos->data->fork[philos->l_fork]);
}

void ft_sleep(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->look_sleep);
	ft_write(SLEEPING, philos);
	ft_usleep(philos->data->time_to_sleep, philos);
	pthread_mutex_unlock(&philos->data->look_sleep);
	ft_write(THINKING, philos);
}

// int check_finished(t_philo *philos, t_data *data)
// {
// 	int i;
// 	int c;

// 	i = 0;
// 	c = 0;
// 	while(i < data->nphilo)
// 	{
// 		if(philos[i].count == philos[i].data->num_meal)
// 			c++;
// 	}
// 	if (c == data->nphilo)
// 		return (1);
// 	return (0);
// }

void *monitoring(void *arg)
{
	t_philo	*philos;
	
	philos = (t_philo *)arg;

	while(!philos->data->die)
	{
	
			int i = 0;
			while(i < philos->data->nphilo)
			{
				if(get_time() - philos[i].times_last_eat > philos->data->time_to_die)
				{
					printf(" ana :%ld\n", philos->times_last_eat);
					printf(" ana :%ld\n", philos[i].times_last_eat);
					ft_write(DIED, philos);
					philos->data->die = 1;
					pthread_mutex_unlock(&philos->data->look_die);
					return NULL;
				}
			}
	}
	return NULL;
}
void *retune(void *arg)
{
    t_philo	*philos;
	
	philos = (t_philo *)arg;
	if (philos->id % 2 == 0)
		usleep(100);
	while(!philos->data->die)
	{
		take_fork(philos);
		eat(philos);
		if (philos->data->die)
		{
			return (NULL);
		}
		ft_sleep(philos);
	}
    return NULL;
}

time_t get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_usleep(long long time, t_philo *philos)
{
	(void)philos;
	time_t l = get_time();
	while(get_time() - l < time)
		usleep(100);
		
}

void ft_write(char *str, t_philo *philos)
{
	time_t time;
	pthread_mutex_lock(&philos->data->look_write);
	time = get_time() - philos->data->start;
	if (!philos->data->die)
	{
		printf("%ld %d %s\n", time, philos->id, str);
	}
	pthread_mutex_unlock(&philos->data->look_write);
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
	// philos = malloc(sizeof(t_philo) * data->nphilo);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nphilo);
	while(i < data->nphilo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].count = 0;
		philos[i].eat = 0;
		philos[i].new_time_to_die = data->time_to_die;
		philos[i].times_last_eat = get_time();
		printf("id = %d\n ana :%ld\n",philos[i].id , philos[i].times_last_eat);
		pthread_mutex_init(&(data->fork[i]), NULL);
		pthread_create(&philos[i].thread, NULL, retune, (void*)&philos[i]);
		i++;
	}
	pthread_create(&philos->data->t, NULL, monitoring, (void *)philos);
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
	pthread_mutex_init(&data->look_eting, NULL);
	pthread_mutex_init(&data->look_die, NULL);
	pthread_mutex_init(&data->look_sleep, NULL);
	pthread_mutex_init(&data->look_write, NULL);
	data->nphilo = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_die = ft_atoi(av[2]);
	data->c = 0;
	data->die = 0;
	data->start = get_time();
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->flag == 1)
		data->num_meal = ft_atoi(av[5]);
	else
		data->num_meal = -1;
}

int main(int ac, char **av)
{

	t_data *data;
	t_philo	*philos;

	data = malloc(sizeof(t_data));
	if (ac > 6 || ac < 5 ||  ft_atoi(av[1]) > 200)
	{
		if (ac == 6)
			data->flag = 1;
		else 
			data->flag = 0;
			
		return (1);
	}
	if (parsing(av) == 0)
	{
		write(1, "wrong\n", 6);
		return (0);
	}
	init_data(av, data);
	philos = malloc(sizeof(t_philo) * data->nphilo);
	init_philos(philos, data);
	
	// printf("philo %d\n", data->nphilo);
	// // printf("philo %d\n", data->c);
	// printf("philo %ld\n", (philos[0]).data->time_to_die);
	// printf("philo %ld\n", (philos[0]).data->time_to_eat);
	// printf("philo %ld\n", (philos[0]).data->time_to_sleep);
	// printf("philo %ld\n", philos[i].times_last_eat);
	// while(1)
	// {
	// 	if (check_die(philos, data))
	// 		return 0;
	// }
	return (0);
}
