/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:11:29 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/11 20:06:17 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philos	*philos;

	philos = (t_philos *)philo;
	if (philos->id & 1)
		usleep(600);
	while (1)
	{
		pthread_mutex_lock(&philos->table->forks[philos->right_fork]);
		print_state(philos->table, philos->table->timer, 'f', &philos->id);
		pthread_mutex_lock(&philos->table->forks[philos->left_fork]);
		print_state(philos->table, philos->table->timer, 'f', &philos->id);
		print_state(philos->table, philos->table->timer, 'e', &philos->id);
		philos->last_snack = (timer() - philos->table->timer);
		my_usleep(philos->table->time_to_eat);
		philos->meals++;
		pthread_mutex_unlock(&philos->table->forks[philos->right_fork]);
		pthread_mutex_unlock(&philos->table->forks[philos->left_fork]);
		print_state(philos->table, philos->table->timer, 's', &philos->id);
		my_usleep(philos->table->time_to_sleep);
		print_state(philos->table, philos->table->timer, 't', &philos->id);
	}
	return (NULL);
}

static void	create_threads(t_philos **philo, t_table *table)
{	
	int			i;
	t_philos	*philos;

	i = 0;
	philos = *philo;
	table->timer = timer();
	while (i < table->num_of_philos)
	{
		pthread_create(&philos[i].threads, NULL, routine, &philos[i]);
		pthread_detach(philos[i].threads);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int			i;
	t_table		table;
	t_philos	*philos;

	if (parser(argc, argv, &table) != 1)
		return (0);
	else
	{	
		i = 0;
		philos = malloc(sizeof(t_philos) * table.num_of_philos);
		table.forks = malloc(sizeof(pthread_mutex_t) * table.num_of_forks);
		while (i <= table.num_of_philos)
		{
			pthread_mutex_init(&table.forks[i], NULL);
			i++;
		}
		pthread_mutex_init(&table.mutex_print, NULL);
		initialize_threads(&philos, &table);
		create_threads(&philos, &table);
		if (death_verifier(&philos))
			return (0);
	}
}
