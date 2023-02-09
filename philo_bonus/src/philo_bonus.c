/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:10:28 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/19 19:13:16 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	critical_section(t_philos *philos, int id)
{
	while (1)
	{
		printf("PID = %d | PHILO ID = %d | Entering the critical section..\n",
			getpid(), id);	
		print_state(philos->table, philos->table->timer, 'f', &philos->id);
		sem_wait(philos->table->semaphore);
		print_state(philos->table, philos->table->timer, 'f', &philos->id);
		sem_wait(philos->table->semaphore);
		print_state(philos->table, philos->table->timer, 'e', &philos->id);
		philos->last_snack = (timer() - philos->table->timer);
		my_usleep(philos->table->time_to_eat);
		philos->meals++;
		sem_post(philos->table->semaphore);
		sem_post(philos->table->semaphore);
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
	i = 1;
	pid = getpid();
	printf("PARENT PID = %d\n", pid);
	sem_unlink("Sem");
	pthread_mutex_init(&table.mutex_print, NULL);
	table.semaphore = malloc(sizeof(sem_t *));
	table.semaphore = sem_open("Sem", O_CREAT, 0777, table.num_of_forks);
	philos = malloc(sizeof(t_philos) * table.num_of_philos);
	philos->pid = malloc(sizeof(pid_t) * table.num_of_philos);
	table.timer = timer();
	while (i <= table.num_of_forks)
	{
		if (fork() == 0)
			i++;
		else
		{
			philos->pid[i] = fork();
			break ;
		}
	}
	initialize_processes(&philos, &table);
	int status = 0;
	if (getpid() != pid)
		critical_section(philos, philos->id);
	waitpid(pid, &status, 0);
	if (getpid() != pid)
		kill(getpid(), SIGKILL);
	sem_close(table.semaphore);
	sem_unlink("Sem");
	return (0);
}