/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multijoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 22:26:52 by susami            #+#    #+#             */
/*   Updated: 2022/10/16 22:38:42 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static pthread_cond_t	threadDied = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t	threadMutex = PTHREAD_MUTEX_INITIALIZER;

static int	totalThreads = 0;
static int	numLive = 0;

static int	numUnjoined = 0;

enum tState {
	TS_ALIVE,
	TS_TERMINATED,
	TS_JOINED
};

static struct {
	pthread_t	tid;
	enum tState	state;
	int			sleepTime;
} *thread;

static void *threadFunc(void *arg)
{
	int	idx = (int)arg;
	sleep(thread[idx].sleepTime);
	printf("Thread %d terminating\n", idx);
	pthread_mutex_lock(&threadMutex);
	numUnjoined++;
	thread[idx].state = TS_TERMINATED;
	pthread_mutex_unlock(&threadMutex);
	pthread_cond_signal(&threadDied);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int	idx;

	thread = calloc(argc - 1, sizeof(*thread));
	for (idx = 0; idx < argc - 1; idx++)
	{
		thread[idx].sleepTime = atoi(argv[idx+1]);
		thread[idx].state = TS_ALIVE;
		pthread_create(&thread[idx].tid, NULL, threadFunc, (void *)idx);

	}
	totalThreads = argc - 1;
	numLive = totalThreads;

	while (numLive > 0)
	{
		pthread_mutex_lock(&threadMutex);
		while (numUnjoined == 0)
			pthread_cond_wait(&threadDied, &threadMutex);
		for (idx = 0; idx < totalThreads; idx++)
		{
			if (thread[idx].state == TS_TERMINATED)
			{
				pthread_join(thread[idx].tid, NULL);
				thread[idx].state = TS_JOINED;
				numLive--;
				numUnjoined--;
				printf("Reaped thread %d (numLive = %d)\n", idx, numLive);
			}
		}
		pthread_mutex_unlock(&threadMutex);
	}
	return (0);
}
