/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:40:16 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/19 18:18:54 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_range(t_table *table)
{
	if (atoi_philo(table->args[1]) > 200
		|| atoi_philo(table->args[2]) < 60
		|| atoi_philo(table->args[3]) < 60
		|| atoi_philo(table->args[4]) < 60)
		philo_error(table);
	else
	{
		table->id = 1;
		table->num_of_philos = atoi_philo(table->args[1]);
		table->num_of_forks = atoi_philo(table->args[1]);
		table->time_to_die = atoi_philo(table->args[2]);
		table->time_to_eat = atoi_philo(table->args[3]);
		table->time_to_sleep = atoi_philo(table->args[4]);
		if (table->args[5])
			table->num_of_turns_to_eat = atoi_philo(table->args[5]);
	}
}

void	error_parser(t_table *table)
{
	char	*str;
	int		i;
	int		j;
	int		argument;

	i = 1;
	j = 0;
	argument = 0;
	str = table->args[i];
	while (str)
	{
		j = 0;
		while (str[j] != '\0')
		{
			argument = atoi_philo(str);
			if (str[j] == ' ' || ft_is_digit(str[j])
				|| (str[j] == '+' && ft_is_digit(str[j + 1]))
				|| (argument <= 2147483647 || argument >= -2147483648))
				j++;
			else
				philo_error(table);
		}
		str = table->args[i++];
	}
	test_range(table);
}
