/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_func1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:43:01 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/11 19:30:41 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_threads(t_philos **philo, t_table *table)
{
	t_philos	*philos;
	int			i;

	i = 0;
	philos = *philo;
	while (i < table->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].right_fork = (i + 1) % table->num_of_forks;
		philos[i].left_fork = i;
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

static int	turns_to_eat(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->table->num_of_philos)
	{
		if (philos[i].meals >= philos->table->turns)
			i++;
		else
			break ;
		if (i == philos->table->num_of_philos)
		{
			usleep(100);
			pthread_mutex_lock(&philos->table->mutex_print);
			printf("\e[1;32m%lld \e[1;36mEACH PHILO ATE AT LEAST",
				(timer() - philos->table->timer));
			printf(" \e[32m%d\e[0m \e[1;94mTIMES.\e[0m\n",
				philos->table->turns);
			return (1);
		}
	}
	return (0);
}

int	death_verifier(t_philos **philo)
{
	int			i;
	t_philos	*philos;

	philos = *philo;
	while (1)
	{
		i = 0;
		while (i < philos->table->num_of_philos)
		{
			if (((timer() - philos->table->timer) - philos[i].last_snack)
				>= philos->table->time_to_die)
			{
				pthread_mutex_lock(&philos->table->mutex_print);
				printf("\e[1;32m%lld \e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m",
					time_diff(timer(), philos->table->timer), philos[i].id);
				printf(" \e[1;91mDIED ‼\e[0m ​😵​​​\n");
				return (1);
			}
			if (philos->table->turns > 0)
				if (turns_to_eat(philos))
					return (1);
			i++;
		}
	}
	return (0);
}
