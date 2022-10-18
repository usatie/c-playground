/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_static_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:03:06 by susami            #+#    #+#             */
/*   Updated: 2022/10/17 17:58:30 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_COUNTER 10

enum tState {
	TS_ALIVE,
	TS_JOINED
};

struct thread {
	pthread_t		tid;
	pthread_mutex_t	mu;
	int				id;
	int				sleepTime;
	int				counter;
	enum tState		state;
};

void	*threadFunc(void *arg)
{
	int	i;
	struct thread *thread;

	thread = (struct thread *)arg;
	i = 0;
	while (i < MAX_COUNTER)
	{
		sleep(thread->sleepTime);
		pthread_mutex_lock(&thread->mu);
		thread->counter++;
		i++;
		printf("Thread %i: %d\n", thread->id, thread->counter);
		pthread_mutex_unlock(&thread->mu);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int	i;
	int	totalThread;
	int	numJoined = 0;
	struct thread *threads;

	if (argc < 2)
		return (1);
	totalThread = argc - 1;
	threads = calloc(totalThread, sizeof(*threads));
	for (i = 0; i < totalThread; i++)
	{
		threads[i].id = i;
		threads[i].sleepTime = atoi(argv[i + 1]);
		threads[i].state = TS_ALIVE;
		pthread_mutex_init(&threads[i].mu, NULL);
		pthread_create(&threads[i].tid, NULL, threadFunc, &threads[i]);
	}
	while (numJoined < totalThread)
	{
		for (i = 0; i < totalThread; i++)
		{
			if (threads[i].state == TS_ALIVE)
			{
				pthread_mutex_lock(&threads[i].mu);
				if (threads[i].counter == MAX_COUNTER)
				{
					pthread_join(threads[i].tid, NULL);
					threads[i].state = TS_JOINED;
					numJoined++;
					printf("Thread %d joined.\n", i);
					pthread_mutex_unlock(&threads[i].mu);
					pthread_mutex_destroy(&threads[i].mu);
				}
				else
				{
					pthread_mutex_unlock(&threads[i].mu);
				}
			}
		}
		usleep(1000);
	}
	free(threads);
	exit(0);
}
