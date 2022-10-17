/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:05:51 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/11 23:07:47 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parser(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
	{
		printf("\e[1;90mARGUMENTS ARE EITHER\e[0m \e[4;1;31m");
		printf("5\e[0m\e[1;90m OR\e[0m \e[1;4;31m6\e[0m \e[1;33m‼\n");
		return (0);
	}
	if (error_parser(argv) || test_range_and_parse(table, argv))
	{
		printf("\e[4;1;31mINVALID\e[0m \e[1;90mARGUMENTS \e[1;33m‼\n");
		return (0);
	}
	return (1);
}

int	test_range_and_parse(t_table *table, char **argv)
{
	int	i;

	if (atoi_philo(argv[1]) > 200 || atoi_philo(argv[1]) <= 0
		|| atoi_philo(argv[2]) < 60 || atoi_philo(argv[3]) < 60
		|| atoi_philo(argv[4]) < 60)
		return (1);
	table->num_of_philos = atoi_philo(argv[1]);
	table->num_of_forks = atoi_philo(argv[1]);
	table->time_to_die = atoi_philo(argv[2]);
	table->time_to_eat = atoi_philo(argv[3]);
	table->time_to_sleep = atoi_philo(argv[4]);
	if (argv[5])
	{
		i = 0;
		while (argv[5][i])
		{
			if (atoi_philo(argv[5]) != -1 && atoi_philo(argv[5]) > 0)
				i++;
			else
				return (1);
		}	
		table->turns = atoi_philo(argv[5]);
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
