/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:25:53 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/06 04:15:04 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
			&philo_routine, &data->philos[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

void *monitoring(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (!data->is_anyone_dead)
	{
		i = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_lock(&data->status_mutex);
			if (get_time() - data->philos[i].last_meal_time 
				> data->time_to_die)
			{
				print_message(data, i + 1, "died");
				data->is_anyone_dead = 1;
				pthread_mutex_unlock(&data->status_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->status_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_data		data;
	int			status;
	pthread_t	monitor;

	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	status = init_data(&data, ac, av);
	if (status)
		return (status);
	if (pthread_create(&monitor, NULL, &monitoring, &data))
		return (1);
	status = start_simulation(&data);
	pthread_join(monitor, NULL);
	return (status);
}