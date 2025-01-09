/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:31:13 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/09 11:36:21 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_sleep(t_philo *philo)
{
	print_message(philo->data, philo->id, "is sleeping");
	if (philo->data->time_to_sleep > philo->data->time_to_die)
	{
		usleep(philo->data->time_to_die * 1000);
		return ;
	}
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->status_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->status_mutex);
}

void	philo_eat(t_philo *philo)
{
	long long	start_time;

	pthread_mutex_lock(philo->left_fork);
	print_message(philo->data, philo->id, "has taken a fork");
	if (philo->data->philo_num > 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo->data, philo->id, "has taken a fork");
		start_time = get_time();
		pthread_mutex_lock(&philo->data->status_mutex);
		philo->is_eating = 1;
		philo->last_meal_time = start_time;
		pthread_mutex_unlock(&philo->data->status_mutex);
		print_message(philo->data, philo->id, "is eating");
		while (get_time() - start_time < philo->data->time_to_eat)
		{
			if (philo->data->is_anyone_dead == 1)
				break ;
			usleep(100);
		}
		philo_eat_count(philo);
	}
	pthread_mutex_unlock(philo->left_fork);
	if (philo->data->philo_num > 1)
		pthread_mutex_unlock(philo->right_fork);
}

int	check_if_done(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->status_mutex);
	result = (philo->data->is_anyone_dead || (philo->data->must_eat != -1 && \
		philo->eat_count >= philo->data->must_eat));
	pthread_mutex_unlock(&philo->data->status_mutex);
	return (result);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		philo_think(philo);
		usleep(1000);
	}	
	if (philo->data->philo_num == 1)
	{
		philo_eat(philo);
		philo_think(philo);
		return (NULL);
	}
	while (!check_if_done(philo))
	{
		philo_think(philo);
		philo_eat(philo);
		if (check_if_done(philo))
			break ;
		philo_sleep(philo);
		if (check_if_done(philo))
			break ;
	}
	return (NULL);
}
