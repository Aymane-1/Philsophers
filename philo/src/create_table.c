/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:43:01 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/01 18:45:35 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*create_table(char *argv)
{
	t_table			*table;
	int				i;
	pthread_mutex_t forks[atoi_philo(argv)];
	
	i = 0;
	table = NULL;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		exit(-1);
	table->num_of_philos = 0;
	table->num_of_forks = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->num_of_turns_to_eat = 0;
	table->elapsed_time = timer();
	pthread_mutex_init(&table->mutex_print, NULL);
	return (table);
}

t_philos	*create_philos(t_table *table, char **argv)
{
	t_philos	*philos;
	int			nb_philos;
	int			i;

	i = 0;
	nb_philos = atoi_philo(argv[1]); 
	philos = malloc(sizeof(t_philos) * nb_philos);
	if (!philos)
		exit(1);
	philos->forks = malloc(sizeof(pthread_mutex_t) * nb_philos);
	philos->forks = &philos->forks[0];
	while (i < nb_philos)
	{
		pthread_mutex_init(&philos->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		philos[i].id = i;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % nb_philos;
		philos[i].shared_data = table;
		i++;
	}
	return (philos);
}
