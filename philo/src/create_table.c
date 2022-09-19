/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:43:01 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/19 19:10:06 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*create_table(t_table *table, char **args)
{
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
	return (table);
}
