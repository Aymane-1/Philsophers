/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:10:28 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/16 12:33:36 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	critical_section(t_philos *philos)
{
	if (philos->id % 2)
		usleep(600);
	while (1)
	{
		sem_post(philos->table->semaphore);
		print_state(philos->table, philos->table->timer, 'f', &philos->id);
		sem_post(philos->table->semaphore);
		print_state(philos->table, philos->table->timer, 'f', &philos->id);
		print_state(philos->table, philos->table->timer, 'e', &philos->id);
		philos->last_snack = (timer() - philos->table->timer);
		my_usleep(philos->table->time_to_eat);
		philos->meals++;
		sem_wait(philos->table->semaphore);
		sem_wait(philos->table->semaphore);
		print_state(philos->table, philos->table->timer, 's', &philos->id);
		my_usleep(philos->table->time_to_sleep);
		print_state(philos->table, philos->table->timer, 't', &philos->id);
	}
}

int	main(int argc, char **argv)
{
	int			i;
	int			pid;
	t_table		table;
	t_philos	*philos;

	if (parser(argc, argv, &table) != 1)
		return (0);
	i = 0;
	pid = getpid();
	printf("\e[31;1mPARENT PID = %d\e[0m\n", pid);
	sem_unlink("Sem");
	table.semaphore = malloc(sizeof(sem_t *));
	pthread_mutex_init(&table.mutex_print, NULL);
	table.semaphore = sem_open("Sem", O_CREAT, 0777, 0 );
	philos = malloc(sizeof(t_philos *) * table.num_of_philos);
	table.timer = timer();
	while (i < table.num_of_forks)
	{
		if (fork() == 0)
			i++;
		else
			break ;
	}
	initialize_processes(&philos, &table);
	if (getpid() != pid)
		critical_section(&philos[i]);
	// sem_close(table.semaphore);
	sem_unlink("Sem");
	return (0);
}