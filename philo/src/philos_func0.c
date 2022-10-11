/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_func0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:51:37 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/11 16:24:17 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_digit(int a)
{
	if (a >= 0 && a <= 9)
		return (1);
	else
		return (0);
}

long	atoi_philo(char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num = num * 10 + (str[i] - '0');
			i++;
		}
		else
			return (-1);
	}
	return (num);
}

long long	time_diff(long long end, long long start)
{
	return (end - start);
}

long long	timer(void)
{
	struct timeval	time_start;
	long long		milli;

	gettimeofday(&time_start, NULL);
	milli = (time_start.tv_sec * 1000) + (time_start.tv_usec / 1000);
	return (milli);
}

void	my_usleep(long long time)
{
	long long	current;

	current = timer();
	while ((timer() - time) < current)
		usleep(100);
}
