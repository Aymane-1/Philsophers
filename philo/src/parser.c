/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:40:16 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/18 15:03:04 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			if (argument > 2147483647 || argument < -2147483648)
				philo_error(table);
			if (str[j] == ' ' || ft_is_digit(str[j])
				|| (str[j] == '+' && ft_is_digit(str[j + 1])))
				j++;
			else
			{
				philo_error(table);
				exit(-1);
			}
		}
		str = table->args[i++];
	}
}

