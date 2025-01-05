/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:04:11 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/02 17:59:22 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int				id;
	int				group_num;
	int				is_eating;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal_time;
	int				eat_count;
	struct s_data	*data;
}t_philo;

typedef struct s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_anyone_dead;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	status_mutex;
	t_philo			*philos;
}t_data;

// main.c
int			main(int ac, char **av);
void		*monitoring(void *arg);

// init.c
int			init_data(t_data *data, int ac, char **av);
int			init_mutex(t_data *data);
int			init_philos(t_data *data);

// philo_routin.c
void		*philo_routine(void *arg);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
int			check_if_done(t_philo *philo);

// util.c
int			ft_atoi(const char *str);
long long	get_time(void);
void		print_message(t_data *data, int id, char *str);

#endif