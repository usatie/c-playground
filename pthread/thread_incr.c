/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_incr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:38:42 by susami            #+#    #+#             */
/*   Updated: 2022/10/16 21:15:04 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMLOOP 100000
static int	glob = 0;

static void	*increment(void *arg)
{
	int	i, loc;

	(void)arg;
	for (i = 0; i < NUMLOOP; i++)
	{
		loc = glob;
		loc++;
		glob = loc;
	}
	return (NULL);
}

static pthread_mutex_t	mu = PTHREAD_MUTEX_INITIALIZER;
static void	*mutex_increment(void *arg)
{
	int	i, loc;

	(void)arg;
	for (i = 0; i < NUMLOOP; i++)
	{
		pthread_mutex_lock(&mu);
		loc = glob;
		loc++;
		glob = loc;
		pthread_mutex_unlock(&mu);
	}
	return (NULL);
}

void	increments(void)
{
	glob = 0;
	increment(NULL);
	increment(NULL);
	printf("increments: glob = %d\n", glob);
}

void	thread_increments(void)
{
	pthread_t	t1, t2;
	int			s;

	glob = 0;
	pthread_create(&t1, NULL, increment, NULL);
	pthread_create(&t2, NULL, increment, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("thread_increments: glob = %d\n", glob);
}

void	thread_mutex_increments(void)
{
	pthread_t	t1, t2;
	int			s;

	glob = 0;
	pthread_create(&t1, NULL, mutex_increment, NULL);
	pthread_create(&t2, NULL, mutex_increment, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("thread_mutex_increment: glob = %d\n", glob);
}

int	main(void)
{
	increments();
	thread_increments();
	thread_mutex_increments();
	exit(EXIT_SUCCESS);
}
