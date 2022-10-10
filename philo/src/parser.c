/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:40:16 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/10 21:40:57 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	test_range_and_parse(t_table *table, char **argv)
{
	if (atoi_philo(argv[1]) > 200 || atoi_philo(argv[1]) <= 0
		|| atoi_philo(argv[2]) < 60 || atoi_philo(argv[3]) < 60
		|| atoi_philo(argv[4]) < 60)
		return (1);
		table->num_of_philos = atoi_philo(argv[1]);
		table->num_of_forks = atoi_philo(argv[1]);
		table->time_to_die = atoi_philo(argv[2]);
		table->time_to_eat = atoi_philo(argv[3]);
		table->time_to_sleep = atoi_philo(argv[4]);
		table->elapsed_time = timer();
		table->wasted = 0;
		if (argv[5])
		{
			int i = 0;
			while (argv[5][i])
			{
				if (atoi_philo(argv[5]) != -1 && atoi_philo(argv[5]) > 0)
					i++;
				else
					return (1);
			}	
			table->num_of_turns_to_eat = atoi_philo(argv[5]);
		}
		return (0);
}

int	error_parser(char **argv)
{
	char	*str;
	int		i;
	int		j;
	long	argument;
	
	i = 1;
	argument = 0;
	str = argv[i];
	while (str)
	{
		if (atoi_philo(str) == -1)
			return (1);
		j = 0;
		while (str[j] != '\0')
		{
			argument = atoi_philo(str);
			if (str[j] == ' '
				|| (str[j] == '+' && ft_is_digit(str[j + 1]))
				|| (argument <= 2147483647 || argument >= -2147483648))
				j++;
			return (0);
		}
		str = argv[i++];
	}
	return (0);
}
