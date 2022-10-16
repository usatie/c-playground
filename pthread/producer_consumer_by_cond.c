/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   producer_consumer_by_cond.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:55:28 by susami            #+#    #+#             */
/*   Updated: 2022/10/16 22:15:19 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pthread_mutex_t	mu = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t	cond = PTHREAD_COND_INITIALIZER;
static int				avail = 0;

void	produce(void)
{
	pthread_mutex_lock(&mu);
	avail++;
	pthread_mutex_unlock(&mu);
	pthread_cond_signal(&cond); /* Wake sleeping consumer */
	/* signal() can be called before unlock().
	 * In either order it works fine. */
}

void	*threadFunc(void *arg)
{
	int	i;

	(void)arg;
	for (i = 0; i < 10000; i++)
	{
		produce();
		if (i % 1000 == 0)
			printf("Produced [%d]\n", i);
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
	int	consumed = 0;
	while (1)
	{
		pthread_mutex_lock(&mu);
		while (avail == 0)
			pthread_cond_wait(&cond, &mu); /* Wait for something to consume */
		while (avail > 0)
		{
			/* Do something with produced unit */
			avail--;
			consumed++;
			if (consumed % 1000 == 0)
				printf("Consumed [%d]\n", consumed);
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
