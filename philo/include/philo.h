/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:11:32 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/02 21:54:35 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H 

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philos t_philos;

typedef struct s_table
{
	long long			elapsed_time;
	int					num_of_philos;
	int					num_of_forks;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_turns_to_eat;
	pthread_mutex_t		mutex_print;
	t_philos 			*philos;
} t_table;

typedef struct s_philos
{
	pthread_t			philosophers;
	pthread_mutex_t		forks;
	int					id;
	t_table		*shared_data;
} t_philos;


int			ft_is_digit(int a);
long		atoi_philo(char *str);
void		error_parser(t_philos *philos, char **argv);
void		test_range_and_parse(t_table *table, char **argv);
void		philo_error(t_philos *philos);
void		create_table(t_table *table);
t_philos	*create_philos(t_table table, char **argv);
long long	timer();

#	endif