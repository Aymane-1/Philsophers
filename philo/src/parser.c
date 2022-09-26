/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:40:16 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/26 19:55:29 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_range(t_philos *philos)
{
	if (atoi_philo(philos->shared_data->args[1]) > 200
		|| atoi_philo(philos->shared_data->args[2]) < 60
		|| atoi_philo(philos->shared_data->args[3]) < 60
		|| atoi_philo(philos->shared_data->args[4]) < 60)
		philo_error(philos);
	else
	{
		philos->shared_data->num_of_philos = atoi_philo(philos->shared_data->args[1]);
		philos->shared_data->num_of_forks = atoi_philo(philos->shared_data->args[1]);
		philos->shared_data->time_to_die = atoi_philo(philos->shared_data->args[2]);
		philos->shared_data->time_to_eat = atoi_philo(philos->shared_data->args[3]);
		philos->shared_data->time_to_sleep = atoi_philo(philos->shared_data->args[4]);
		if (philos->shared_data->args[5])
			philos->shared_data->num_of_turns_to_eat = atoi_philo(philos->shared_data->args[5]);
	}
}

void	error_parser(t_philos *philos)
{
	char	*str;
	int		i;
	int		j;
	int		argument;
	i = 1;
	j = 0;
	argument = 0;
	str = philos->shared_data->args[i];
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
				philo_error(philos);
		}
		str = philos->shared_data->args[i++];
	}
	test_range(philos);
}
