/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:25:39 by aechafii          #+#    #+#             */
/*   Updated: 2022/09/29 21:31:21 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int g = 0;

void	routine()
{
	int i = 0;
	while (i++ < 1000000)
		g++;
}

int main()
{
	pthread_t th;
	pthread_t th1;
	pthread_create(&th, NULL, (void *)&routine, NULL);
	pthread_join(th, NULL);
	pthread_create(&th1, NULL, (void *)&routine, NULL);
	pthread_join(th1, NULL);
	printf("%d\n", g);
}