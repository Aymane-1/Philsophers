/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:11:32 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/19 19:08:33 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H 

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>

typedef struct s_philos
{
	int			philosophers;
	int			forks;
	int			id;
	t_table		*table;
} t_philo;


typedef struct s_table
{
	char		**args;
	int			num_of_philos;
	int			num_of_forks;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_turns_to_eat;
} t_table;

int			ft_is_digit(int a);
long		atoi_philo(char *str);
void		error_parser(t_table *table);
void		test_range(t_table *table);
void		philo_error(t_table *table);
t_table		*create_table(t_table *table, char **args);

#	endif