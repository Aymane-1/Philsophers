/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:11:32 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/26 19:54:42 by aechafii         ###   ########.fr       */
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

typedef struct s_table
{
	char				**args;
	long long			elapsed_time;
	int					num_of_philos;
	int					num_of_forks;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_turns_to_eat;
	pthread_mutex_t		mutex_print;
} t_table;

typedef struct s_philos
{
	int					id;
	pthread_t			philosophers;
	pthread_mutex_t		forks;
	struct s_table		*shared_data;
} t_philos;

int			ft_is_digit(int a);
long		atoi_philo(char *str);
void		error_parser(t_philos *philos);
void		test_range(t_philos *philos);
void		philo_error(t_philos *philos);
t_philos	*create_table(char **args);
t_philos	*create_philos(t_table *table);
long long	timer();

#	endif