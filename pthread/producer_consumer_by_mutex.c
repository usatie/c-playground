/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   producer_consumer_by_mutex.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:25:09 by susami            #+#    #+#             */
/*   Updated: 2022/10/16 21:36:37 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

static pthread_mutex_t	mu = PTHREAD_MUTEX_INITIALIZER;
static int				avail = 0;

void	produce(void)
{
	pthread_mutex_lock(&mu);
	avail++;
	pthread_mutex_unlock(&mu);
}

void	*threadFunc(void *arg)
{
	int	i;

	(void)arg;
	for (i = 0; i < 1000; i++)
	{
		produce();
	}
	return (NULL);
}

void	create_producer_thread(void)
{
	pthread_t	t;

	pthread_create(&t, NULL, threadFunc, NULL);
}

void	make_this_thread_consumer(void)
{
	while (1)
	{
		pthread_mutex_lock(&mu);
		while (avail > 0)
		{
			/* Do something with produced unit */
			avail--;
		}
		pthread_mutex_unlock(&mu);
	}
}

int	main(void)
{
	create_producer_thread();
	make_this_thread_consumer();
	return (0);
}
