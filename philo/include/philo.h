/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:11:32 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/11 19:30:47 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

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
	pthread_mutex_t		*forks;
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
int			death_verifier(t_philos **philo);
void		create_table(t_table *table);
void		initialize_threads(t_philos **philo, t_table *table);
void		my_usleep(long long time);
void		print_state(t_table *table, long long time, char state, int *id);
long		atoi_philo(char *str);
long long	timer(void);
long long	time_diff(long long end, long long start);

#	endif