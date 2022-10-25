/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:16:39 by susami            #+#    #+#             */
/*   Updated: 2022/10/18 17:23:33 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

static int				counter = 0;
static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;

void	*writeFunc(void *arg)
{
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mtx);
		counter++;
		pthread_mutex_unlock(&mtx);
		if (counter % 10000 == 0)
		{
			printf("  write: %d\n", counter);
		}
	}
	return (NULL);
}

void	*readFunc(void *arg)
{
	for (int i = 0; i < 100; i++)
	{
		pthread_mutex_lock(&mtx);
		printf("  read: %d\n", counter);
		pthread_mutex_unlock(&mtx);
		usleep(10);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	t1, t2;

	pthread_create(&t1, NULL, writeFunc, NULL);
	pthread_create(&t2, NULL, readFunc, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}
