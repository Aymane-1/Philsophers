/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_func1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:43:01 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/09 21:18:29 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_threads(t_philos **philo, t_table *table)
{
	t_philos	*philos = *philo;
	int			i;
	
	i = 0;
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
		if (state == 'f')
			printf("\e[1;32m%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mhas taken a fork\e[0m\n"
					,time_diff(timer(), time), *id);
		else if (state == 'e')
			printf("\e[1;32m%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mis eating\e[0m\n"
					,time_diff(timer(), time), *id);
		else if (state == 's')
			printf("\e[1;32m%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mis sleeping\e[0m\n"
					,time_diff(timer(), time), *id);
		else if (state == 't')
			printf("\e[1;32m%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mis thinking\e[0m\n"
					,time_diff(timer(), time), *id);
		pthread_mutex_unlock(&table->mutex_print);
}

int		death_verifier(t_philos **philo)
{
	int			i;
	int			j;
	t_philos	*philos = *philo;

	while (!(philos->table->wasted))
	{
		i = 0;
		while (i < philos->table->num_of_philos)
		{
			if (((timer() - philos->table->elapsed_time) - philos[i].last_snack) >= philos->table->time_to_die)
			{
				pthread_mutex_lock(&philos->table->mutex_print);
				printf("\e[1;32m%lld \e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;91mDIED ‼\e[0m ​😵​​​\n",
				 (timer() - philos->table->elapsed_time), i + 1);
				philos->table->wasted = 1;
				return (1);
			}
			if (philos->table->num_of_turns_to_eat != -1)
			{
				j = 0;
				while (j < philos->table->num_of_philos)
				{
					if (philos[j].meals >= philos->table->num_of_turns_to_eat)
					 	j++;
					else
						break;
					if (j == philos->table->num_of_philos)
					{
						philos->table->wasted = 1;
						usleep(100);
						printf("\e[1;32m%lld \e[1;36mEVERY PHILOSOPHER ATE AT LEAST \e[32m%d\e[0m \e[1;94mTIMES.\e[0m\n",
						 (timer() - philos->table->elapsed_time), philos->table->num_of_turns_to_eat);
						return(1);
					}
				}
			}
			i++;
		}
	}
	return (0);
}

void	my_usleep(long long time) 
{
	long long	current;

	current = timer();
	while ((timer() - time) < current)
		usleep(100);
}

long long	time_diff(long long end, long long start)
{
	return (end - start);
}