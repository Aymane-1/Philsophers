/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:07:39 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/14 13:21:14 by aechafii         ###   ########.fr       */
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
	pthread_mutex_t		mutex_print;
	sem_t				semaphore;
}	t_table;

typedef struct s_philos
{
	pthread_t			threads;
	int					id;
	int					left_fork;
	int					right_fork;
	int					meals;
	long long			last_snack;
	struct s_table		*table;
}	t_philos;

int			parser(int argc, char **argv, t_table *table);
int			error_parser(char **argv);
int			test_range_and_parse(t_table *table, char **argv);
int			ft_is_digit(int a);
void		initialize_processes(t_philos **philo, t_table *table);
void		my_usleep(long long time);
long		atoi_philo(char *str);
long long	timer(void);
long long	time_diff(long long end, long long start);

#	endif