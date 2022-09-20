/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:43:01 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/20 11:20:44 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*create_philos(t_philos *philos, char **args)
{
	philos = (t_philos *)malloc(sizeof(t_philos));
	if (!philos)
		exit(1);
	philos->shared_data->args = args;
	philos->shared_data->num_of_philos = 0;
	philos->shared_data->num_of_forks = 0;
	philos->shared_data->time_to_die = 0;
	philos->shared_data->time_to_eat = 0;
	philos->shared_data->time_to_sleep = 0;
	philos->shared_data->num_of_turns_to_eat = 0;
	return (philos);
}
