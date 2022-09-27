/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:43:01 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/27 19:15:30 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*create_table()
{
	t_table		*table;
	int			status;
	
	status = 0;
	table = NULL;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		exit(1);
	table->num_of_philos = 0;
	table->num_of_forks = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->num_of_turns_to_eat = 0;
	table->elapsed_time = timer();
	status = pthread_mutex_init(&table->mutex_print, NULL);
	if (status != 0)
		exit(-1);
	return (table);
}

t_philos	*create_philos(t_table *table, char **argv)
{
	t_philos	*philos;
	int			nb_philos;
	int			i;

	i = 1;
	nb_philos = atoi_philo(argv[1]); 
	philos = (t_philos *)malloc(sizeof(t_philos) * nb_philos);
	if (!philos)
		exit(1);
	while (i <= nb_philos)
	{
		philos[i].id = i;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % nb_philos;
		philos[i].shared_data = table;
		i++;
	}
	return (philos);
}
