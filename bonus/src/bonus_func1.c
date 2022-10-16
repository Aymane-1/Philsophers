/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_func1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:22:39 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/16 10:50:05 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	initialize_processes(t_philos **philo, t_table *table)
{
	int			i;
	t_philos	*philos;

	i = 0;
	philos = *philo;
	while (i < table->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].last_snack = 0;
		philos[i].table = table;
		i++;
	}
}

void	print_state(t_table *table, long long time, char state, int *id)
{
	pthread_mutex_lock(&table->mutex_print);
	printf("\e[1;32m%lld \e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m",
		time_diff(timer(), time), *id);
	if (state == 'f')
		printf(" \e[1;3mhas taken a fork\e[0m\n");
	else if (state == 'e')
		printf(" \e[1;3mis eating\e[0m\n");
	else if (state == 's')
		printf(" \e[1;3mis sleeping\e[0m\n");
	else if (state == 't')
		printf(" \e[1;3mis thinking\e[0m\n");
	pthread_mutex_unlock(&table->mutex_print);
}