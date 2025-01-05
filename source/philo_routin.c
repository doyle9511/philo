/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:31:13 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/02 17:31:31 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_sleep(t_philo *philo)
{
	print_message(philo->data, philo->id, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void philo_think(t_philo *philo)
{
	print_message(philo->data, philo->id, "is thinking");
}

void philo_eat(t_philo *philo)
{
	long long start_time;
		
	pthread_mutex_lock(philo->left_fork);
	print_message(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo->data, philo->id, "has taken a fork");
		
	start_time = get_time();
	pthread_mutex_lock(&philo->data->status_mutex);
	philo->is_eating = 1;
	philo->last_meal_time = start_time;
	pthread_mutex_unlock(&philo->data->status_mutex);
		
	print_message(philo->data, philo->id, "is eating");
	while (get_time() - start_time < philo->data->time_to_eat)
		usleep(100);
	philo->eat_count++;
		
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int check_if_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->status_mutex);
	if (philo->data->is_anyone_dead)
	{
		pthread_mutex_unlock(&philo->data->status_mutex);
		return (1);
	}
	if (philo->data->must_eat != -1 && 
		philo->eat_count >= philo->data->must_eat)
	{
		pthread_mutex_unlock(&philo->data->status_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->status_mutex);
	return (0);
}

void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
		
	while (!check_if_done(philo))
	{
		philo_eat(philo);
		if (check_if_done(philo))
			break;
		philo_sleep(philo);
		if (check_if_done(philo))
			break;
		philo_think(philo);
	}
	return (NULL);
}
