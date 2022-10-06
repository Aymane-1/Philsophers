/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:11:29 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/06 21:06:39 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timer()
{
	struct timeval	time_start;
	long long		milli;

	gettimeofday(&time_start, NULL);
	milli = (time_start.tv_sec * 1000) + (time_start.tv_usec / 1000);
	return (milli);
}

void	*routine(void *philo)
{
	t_philos *philos = (t_philos *)philo;
	if (philos->id % 2)
		usleep(800);
	while (1)
	{
		pthread_mutex_lock(&philos->table->forks[philos->right_fork]);
		print_state(philos->table, philos->table->elapsed_time, 'f', &philos->id);
		pthread_mutex_lock(&philos->table->forks[philos->left_fork]);
		print_state(philos->table, philos->table->elapsed_time, 'f', &philos->id);
		print_state(philos->table, philos->table->elapsed_time, 'e', &philos->id);
		my_usleep(philos->table->time_to_eat);
		philos->last_snack = timer();
		// printf("last meal = %lld\n", philos->last_snack);
		philos->nb_meals++;
		pthread_mutex_unlock(&philos->table->forks[philos->right_fork]);
		pthread_mutex_unlock(&philos->table->forks[philos->left_fork]);
		print_state(philos->table, philos->table->elapsed_time, 's', &philos->id);
		my_usleep(philos->table->time_to_sleep);
		print_state(philos->table, philos->table->elapsed_time, 't', &philos->id);
		// death_verifier(&philos);
	}
	return NULL;
}

static void	create_threads(t_philos **philo, t_table *table)
{	
	int	i;
	t_philos *philos = *philo;
	
	i = 0;
	table->elapsed_time = timer();
	while (i < table->num_of_philos)
	{
		pthread_create(&philos[i].threads, NULL, routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < table->num_of_philos)
	{
		pthread_join(philos[i].threads, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int			i;
	t_table		table;
	t_philos	*philos;

	if (argc < 5 || argc > 6)
	{
		printf("Error\n");	
		exit(-1);
	}
	else
	{	
		i = 0;
		error_parser(argv);
		test_range_and_parse(&table, argv);
		philos = malloc(sizeof(t_philos) * table.num_of_philos);
		table.forks = malloc(sizeof(pthread_mutex_t) * table.num_of_forks);
		while (i++ < table.num_of_philos)
			pthread_mutex_init(&table.forks[i], NULL);
		pthread_mutex_init(&table.mutex_print, NULL);
		initialize_threads(&philos, &table);
		create_threads(&philos, &table);
		death_verifier(&philos);
	}
}
