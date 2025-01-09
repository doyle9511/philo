/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:32:50 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/09 11:24:17 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_message(t_data *data, int id, char *str)
{
	if (str[0] != 'd')
		pthread_mutex_lock(&data->status_mutex);
	if (!data->is_anyone_dead)
		printf("%lld %d %s\n", get_time() - data->start_time, id, str);
	if (str[0] != 'd')
		pthread_mutex_unlock(&data->status_mutex);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Error: wrong argument\n");
			return (-1);
		}
		i++;
	}
	if (i > 11)
	{
		printf("Error: too much input\n");
		return (-1);
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

void	philo_think(t_philo *philo)
{
	print_message(philo->data, philo->id, "is thinking");
}
