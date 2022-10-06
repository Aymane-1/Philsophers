/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:43:01 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/06 15:35:15 by aechafii         ###   ########.fr       */
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
		philos[i].id = (i + 1);
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % table->num_of_forks;
		philos[i].nb_meals = 0;
		philos[i].last_snack = 0;
		philos[i].table = table;
		i++;
	}
}

void	print_state(t_table *table, long long time, char state, int *id)
{
		pthread_mutex_lock(&table->mutex_print);
		if (state == 'f')
			printf("%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mhas taken a fork\e[0m\n"
					,time_diff(timer(), time), *id);
		else if (state == 'e')
			printf("%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mis eating\e[0m\n"
					,time_diff(timer(), time), *id);
		else if (state == 's')
			printf("%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mis sleeping\e[0m\n"
					,time_diff(timer(), time), *id);
		else if (state == 't')
			printf("%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mis thinking\e[0m\n"
					,time_diff(timer(), time), *id);
		pthread_mutex_unlock(&table->mutex_print);
}

int		death_verifier(t_philos **philo)
{
	int		i;
	t_philos * philos = *philo;

	printf("num of philos = %d\n", philos->table->num_of_philos);
	i = 0;
	while (i < philos->table->num_of_philos)
	{
		printf("time to die = %d,  last meal = %lld\n", philos->table->time_to_die, timer() - philos->last_snack);
		if (philos[i].table->time_to_die > (time_diff(timer(), philos->last_snack)))	 // save last time of eat and check if its longer than time_to_die
		{
			pthread_mutex_lock(&philos->table->mutex_print);
			printf("%lld \e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;91mDIED ‼\e[0m ​😵​​​\n", (timer() - philos->table->elapsed_time) ,philos->id + 1);
			return(1);
		}
		i++;
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