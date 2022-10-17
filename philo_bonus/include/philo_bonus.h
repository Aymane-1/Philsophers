/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:07:39 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/16 18:56:20 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H 

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <semaphore.h>

typedef struct s_table
{
	int					num_of_philos;
	int					num_of_forks;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					turns;
	long long			timer;
	sem_t				*semaphore;
	pthread_mutex_t		mutex_print;
}	t_table;

typedef struct s_philos
{
	pthread_t			threads;
	pid_t				*pid;
	int					id;
	int					meals;
	long long			last_snack;
	struct s_table		*table;
}	t_philos;

int			parser(int argc, char **argv, t_table *table);
int			error_parser(char **argv);
int			test_range_and_parse(t_table *table, char **argv);
int			ft_is_digit(int a);
void		print_state(t_table *table, long long time, char state, int *id);
void		initialize_processes(t_philos **philo, t_table *table);
void		my_usleep(long long time);
long		atoi_philo(char *str);
long long	timer(void);
long long	time_diff(long long end, long long start);

#	endif