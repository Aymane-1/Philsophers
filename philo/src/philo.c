/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:11:29 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/20 18:21:18 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philos *philos)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	printf("%d Philosopher %d is thinking\n", current_time.tv_usec, philos->id);
	// pthread_mutex_lock(&philos->shared_data->num_of_forks);
	return NULL;
}

static void	create_mutexes(t_philos *philos)
{
	pthread_mutex_t forks[philos->shared_data->num_of_forks];
	while (philos->id++ < philos->shared_data->num_of_philos)
		pthread_mutex_init(&forks[philos->id], NULL);
}

static void	create_threads(t_philos *philos)
{
	pthread_t philosophers[philos->shared_data->num_of_philos];
	while (philos->id++ < philos->shared_data->num_of_philos)
	{
		pthread_create(&philosophers[philos->id], NULL, (void *)routine, philos);
		usleep(250000);
	}
	create_mutexes(philos);
}

static void	philo(t_philos *philos)
{
	error_parser(philos);
	test_range(philos);
	create_threads(philos);
}

int	main(int argc, char **argv)
{
	t_philos	*philos;

	philos = NULL;
	if (argc < 5 || argc > 6)
		philo_error(philos);
	philos = create_philos(philos, argv);
	philo(philos);
	return (0);
}
