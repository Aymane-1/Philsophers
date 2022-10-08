/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:11:32 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/08 18:46:22 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_table
{
	int					num_of_philos;
	int					num_of_forks;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_turns_to_eat;
	int					wasted;
	long long			elapsed_time;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		*forks;
}	t_table;

typedef struct s_philos
{
	pthread_t			threads;
	int					id;
	int					left_fork;
	int					right_fork; 
	int					nb_meals;
	long long			last_snack;
	struct s_table		*table;
}	t_philos;


int			ft_is_digit(int a);
long		atoi_philo(char *str);
void		error_parser(char **argv);
void		test_range_and_parse(t_table *table, char **argv);
void		philo_error(t_philos *philos);
void		create_table(t_table *table);
void		initialize_threads(t_philos **philo ,t_table *table);
long long	timer();
long long	time_diff(long long end, long long start);
void		my_usleep(long long time);
int			death_verifier(t_philos **philo);
void		print_state(t_table *table, long long time, char state, int *id);

#	endif