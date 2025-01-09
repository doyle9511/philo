/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:32:17 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/09 11:11:42 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (1);
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->status_mutex, NULL))
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (1);
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].is_eating = 0;
		data->philos[i].eat_count = 0;
		data->philos[i].last_meal_time = get_time();
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_num];
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->philo_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	if (data->philo_num == -1 || data->time_to_die == -1 \
		|| data->time_to_eat == -1 || data->time_to_sleep == -1)
		return (1);
	if (ac == 6 && data->must_eat == -1)
		return (1);
	data->is_anyone_dead = 0;
	data->start_time = get_time();
	if (init_mutex(data) != 0)
		return (1);
	if (init_philos(data) != 0)
		return (1);
	return (0);
}
