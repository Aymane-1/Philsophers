/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:43:01 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/26 13:48:36 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*create_table(char **args)
{
	t_table *table;
	t_philos *philos;
	
	philos = NULL;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		exit(1);
	table->args = args;
	table->num_of_philos = 0;
	table->num_of_forks = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->num_of_turns_to_eat = 0;
	table->elapsed_time = timer();
	philos = create_philos(table);
	return (philos);
}

t_philos	*create_philos(t_table *table)
{
	t_philos *philos;
	int	nb_philos;
	int	i = 0;

	nb_philos = atoi_philo(table->args[1]); 
	philos = (t_philos *)malloc(sizeof(t_philos) * nb_philos);
	if (!philos)
		exit(1);
	while (i < nb_philos)
	{
		philos[i].shared_data = table;
		i++;
	}	
	return (philos);
}
