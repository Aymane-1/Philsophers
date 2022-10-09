/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:40:16 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/09 21:19:01 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	test_range_and_parse(t_table *table, char **argv)
{
	if (atoi_philo(argv[1]) > 200
		|| atoi_philo(argv[1]) <= 0
		|| atoi_philo(argv[2]) < 60
		|| atoi_philo(argv[3]) < 60
		|| atoi_philo(argv[4]) < 60)
	{
		printf("Error\n");
		return (1);
	}
	else
	{
			table->num_of_philos = atoi_philo(argv[1]);
			table->num_of_forks = atoi_philo(argv[1]);
			table->time_to_die = atoi_philo(argv[2]);
			table->time_to_eat = atoi_philo(argv[3]);
			table->time_to_sleep = atoi_philo(argv[4]);
			table->elapsed_time = timer();
			table->wasted = 0;
			if (argv[5])
				table->num_of_turns_to_eat = atoi_philo(argv[5]);
			else
				table->num_of_turns_to_eat = -1;
			// if (table->num_of_turns_to_eat == -1)
			// {	
			// 	printf("Error\n");
			// 	return (1);
			// }
			return (0);
	}
}

void	error_parser(char** argv)
{
	char	*str;
	int		i;
	int		j;
	long	argument;
	
	i = 1;
	j = 0;
	argument = 0;
	str = argv[i];
	while (str)
	{
		j = 0;
		while (str[j] != '\0')
		{
			argument = atoi_philo(str);
			if (str[j] == ' ' || (str[j] >= 0 && str[j] <= 9)
				|| (str[j] == '+' && ft_is_digit(str[j + 1]))
				|| (argument <= 2147483647 || argument >= -2147483648))
				j++;
			else
			{
				printf("\033[1;91mERROR ‼\033[0m\n");
				return;
			}
		}
		str = argv[i++];
	}
}
