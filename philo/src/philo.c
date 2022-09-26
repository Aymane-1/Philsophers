/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:11:29 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/26 20:41:57 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	check_death(t_philos *philos)
// {
// 	// long long		time;

// 	if (philos->shared_data->time_to_die > time)
// 		pthread_mutex_lock(&philos->shared_data->mutex_print);
// 		printf("\e[1;90mPHILOSOPHER\e[0m \e[1;33m%d\e[0m \e[1;91mDIED ‼\e[0m ​😵​​​\n", philos->id);
// 		pthread_mutex_unlock(&philos->shared_data->mutex_print);
// 	exit(-1);
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
	pthread_mutex_lock(&philos->shared_data->mutex_print);
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
	pthread_mutex_unlock(&philos->shared_data->mutex_print);
}

void	*routine(t_philos *philos)
{
	if (philos->id & 1)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philos[philos->id].forks);
		print_state(philos, 'f', &philos->id);
		pthread_mutex_lock(&philos[(philos->id + 1) % philos->shared_data->num_of_forks].forks);
		print_state(philos, 'f', &philos->id);
		usleep(philos->shared_data->time_to_eat / 1000);
		print_state(philos, 'e', &philos->id);
		pthread_mutex_unlock(&philos[philos->id].forks);
		pthread_mutex_unlock(&philos[philos->id + 1 % philos->shared_data->num_of_forks].forks);
		print_state(philos, 's', &philos->id);
		usleep(philos->shared_data->time_to_sleep / 1000);
		print_state(philos, 't', &philos->id);
	}
	return NULL;
}

static void	create_threads(t_philos *philos)
{	
	int	i;
	int	status;
	
	i = 0;
	status = 0;
	while (++i < philos->shared_data->num_of_philos)
	{
		philos[i].id = i;
		status = pthread_create(&philos[i].philosophers, NULL, (void *)routine, (void *)(&philos[i]));
		if (status != 0)
			philo_error(philos);
		pthread_detach(philos[i].philosophers);
	}
}

static void	create_mutexes(t_philos *philos)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	pthread_mutex_init(&philos->shared_data->mutex_print, NULL);
	while (i++ < philos->shared_data->num_of_philos)
	{
		status = pthread_mutex_init(&philos[i].forks, NULL);
		if (status != 0)
			philo_error(philos);
	}
}

static void	parser(t_philos *philos)
{
	error_parser(philos);
	test_range(philos);
}

int	main(int argc, char **argv)
{
	t_philos	*philos;

	philos = NULL;
	if (argc < 5 || argc > 6)
		philo_error(philos);
	philos = create_table(argv);
	parser(philos);
	create_mutexes(philos);
	create_threads(philos);
	return (0);
}
