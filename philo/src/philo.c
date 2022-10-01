/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:11:29 by aechafii          #+#    #+#             */
/*   Updated: 2022/10/01 20:11:58 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	check_death(t_philos *philos)
// {
// 	long long		time;

// 	time = timer();
// 	if ((philos->shared_data->time_to_die / 1000) > time)
// 	{	
// 		pthread_mutex_lock(&philos->shared_data->mutex_print);
// 		printf("\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;91mDIED ‼\e[0m ​😵​​​\n", philos->id);
// 		pthread_mutex_unlock(&philos->shared_data->mutex_print);
// 		return (0);
// 	}
// 	else
// 		return (1);
// }

long long	time_diff(long long end, long long start)
{
	return (end - start);
}

long long	timer()
{
	struct timeval	time_start;
	long long		milli;

	gettimeofday(&time_start, NULL);
	milli = (time_start.tv_sec * 1000) + (time_start.tv_usec / 1000);
	return (milli);
}

void	print_state(t_philos *philos, char state, int *id)
{
	long long	time_start = 0;
	time_start = timer();
	printf("lock of print status = %d\n", pthread_mutex_lock(&philos->shared_data->mutex_print));
	if (state == 'f')
		printf("%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mhas taken a fork\e[0m\n"
				,time_diff(timer(), philos->shared_data->elapsed_time), *id);
	else if (state == 'e')
		printf("%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mis eating\e[0m\n"
				,time_diff(timer(), philos->shared_data->elapsed_time), *id);
	else if (state == 's')
		printf("%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mis sleeping\e[0m\n"
				,time_diff(timer(), philos->shared_data->elapsed_time), *id);
	else if (state == 't')
		printf("%lld \e[4m\e[0m\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;3mis thinking\e[0m\n"
				,time_diff(timer(), philos->shared_data->elapsed_time), *id);
	// pthread_mutex_unlock(&philos->shared_data->mutex_print);
	printf("unlock of print status = %d\n", pthread_mutex_unlock(&philos->shared_data->mutex_print));
}

void	*routine(t_philos *philos)
{
	int left_fork = philos->id;
	int right_fork = (philos->id + 1) % philos->shared_data->num_of_philos;
	printf("left fork = %d\n", left_fork);
	printf("right fork = %d\n", right_fork);
	if (philos->id & 1)
		usleep(700);
	while (1)
	{
		printf("Lock status of left_fork = %d\n", pthread_mutex_lock(&philos->forks[right_fork]));
		// printf("philos id = %d\n", philos->id);
		// pthread_mutex_lock(&philos->forks[left_fork]);
		print_state(philos, 'f', &philos->id);
		// pthread_mutex_lock(&philos->forks[right_fork]);
		printf("Lock status of right_fork = %d\n", pthread_mutex_lock(&philos->forks[left_fork]));
		print_state(philos, 'f', &philos->id);
		usleep(philos->shared_data->time_to_eat * 1000);
		print_state(philos, 'e', &philos->id);
		printf("Unlock status of left_fork= %d\n", pthread_mutex_unlock(&philos->forks[right_fork]));
		printf("Unlock status of right_fork = %d\n", pthread_mutex_unlock(&philos->forks[left_fork]));
		// pthread_mutex_unlock(&philos->forks[left_fork]);
		pthread_mutex_unlock(&philos->forks[right_fork]);
		print_state(philos, 's', &philos->id);
		usleep(philos->shared_data->time_to_sleep * 1000);
		print_state(philos, 't', &philos->id);
	}
	return NULL;
}

static void	create_threads(t_philos *philos)
{	
	int	i;
	int	status;
	int	state;
	
	i = 0;
	status = 0;
	state = 0;
	while (i < philos->shared_data->num_of_philos)
	{
		pthread_create(&philos[i].philosophers, NULL, (void *)routine, &philos[i]);
		pthread_join(philos[i].philosophers, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philos	*philos;
	t_table		*table;

	philos = NULL;
	table = NULL;
	if (argc < 5 || argc > 6)
		philo_error(philos);
	table = create_table(argv[1]);
	philos = create_philos(table, argv);
	error_parser(philos, argv);
	test_range_and_parse(table, argv);
	create_threads(philos);
	return (0);
}
