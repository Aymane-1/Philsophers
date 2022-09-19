/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:11:29 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/19 18:58:30 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_table *table)
{
	printf("\nPhilosopher %d is thinking\n", table->data->philosophers[&table->id]);
	pthread_mutex_lock(&table->data->forks[table->id]);
	return NULL;
}

static void	create_threads(t_table *table)
{
	pthread_t philosophers[table->num_of_philos];
	while (table->id++ <= table->num_of_forks)
		pthread_create(&philosophers[table->id], NULL, routine, table);

}
static void	create_mutexes(t_table *table)
{
	pthread_mutex_t forks[table->num_of_forks];
	while (table->id++ <= table->num_of_philos)
		pthread_mutex_init(&forks[table->id], NULL);
}

static void	philo(t_table *table)
{
	error_parser(table);
	test_range(table);
	create_threads(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc < 5 || argc > 6)
		philo_error(table);
	table = create_table(table, argv);
	philo(table);
	return (0);
}
