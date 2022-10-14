/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:10:28 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/14 17:28:44 by aechafii         ###   ########.fr       */
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

// void	critical_section(t_philos **philo)
// {
// 	t_philos *philos;
	
// 	philos = *philo;
// 	sem_wait(&philos->table->semaphore);
// 	print_state(philos->table, philos->table->timer, 'f', &philos->id);
// 	sem_post(&philos->table->semaphore);
// }

int	main(int argc, char **argv)
{
	int			i;
	int			pid;
	t_table		table;
	t_philos	*philos;

	if (parser(argc, argv, &table) != 1)
		return (0);
	else
	{
		i = 0;
		pid = getpid();
		printf("\e[31;1mPARENT PID = %d\e[0m\n", pid);
		while (i < (table.num_of_forks))
		{
			if (fork() == 0)
				i++;
			else
				break ;
		}
		if (getpid() != pid)
		{
			sem_open("Sem", O_CREAT, 0777, table.num_of_forks);
			sem_wait(&table.semaphore);
			printf("pid = %d\n", getpid());
			printf("hello from critical section\n");
			// critical_section(&philos);
			sem_post(&table.semaphore);
		}
		philos = malloc(sizeof(t_philos *) * table.num_of_philos);
		initialize_processes(&philos, &table);
		// create_processes(&philos);
		return (0);
	}
}