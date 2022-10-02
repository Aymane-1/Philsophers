/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:43:01 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/02 21:54:17 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_table(t_table *table)
{
	
	// i = 0;
	// table->philos = (t_philos *)malloc(sizeof(t_philos) * table->num_of_philos);
	// if (!table)
	// 	exit(-1);
	table->num_of_philos = 0;
	table->num_of_forks = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->num_of_turns_to_eat = 0;
	table->elapsed_time = timer();
	// pthread_mutex_init(&table->mutex_print, NULL);
	// return (table);
}

t_philos	*create_philos(t_table table, char **argv)
{
	t_philos	*philos;
	int			nb_philos;
	int			i;

	i = 0;
	nb_philos = atoi_philo(argv[1]); 
	philos = malloc(sizeof(t_philos) * nb_philos);
	if (!philos)
		exit(1);
	// philos->forks = malloc(sizeof(pthread_mutex_t);
	// philos->forks = &philos->forks[0];
	while (i < nb_philos)
	{
		pthread_mutex_init(&philos[i].forks, NULL);
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		philos[i].id = i;
		philos[i].shared_data = &table;
		i++;
	}
	return (philos);
}
