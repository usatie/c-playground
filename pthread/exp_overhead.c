/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_overhead.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:38:34 by susami            #+#    #+#             */
/*   Updated: 2022/10/18 10:16:15 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

#define ONE_SEC_IN_MSEC 1000
#define ONE_MSEC_IN_USEC 1000

struct timeval	start;

int	get_timestamp_ms(void)
{
	struct timeval	now;
	int				ts;

	gettimeofday(&now, NULL);
	ts = (now.tv_sec - start.tv_sec) * ONE_SEC_IN_MSEC;
	ts += (now.tv_usec - start.tv_usec) / ONE_MSEC_IN_USEC;
	return (ts);
}

void	logger(char *msg)
{
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	int						ts;

	pthread_mutex_lock(&mtx);
	ts = get_timestamp_ms();
	printf("%3d %s", ts, msg);
	pthread_mutex_unlock(&mtx);
}

void	*hello(void *arg)
{
	(void)arg;
	//get_timestamp_ms();
	logger("Hello World\n");
	return (NULL);
}

void	*empty(void *arg)
{
	(void)arg;
	return (NULL);
}

void	measure(char *name, void (*f)(void))
{
	gettimeofday(&start, NULL);
	f();
	printf("%s:\n", name);
	logger("ms\n");
}

#define NUM_THREAD 10000

void	bench_pthread_create_join(void)
{
	pthread_t	tids[NUM_THREAD];
	for (int i = 0; i < NUM_THREAD; i++)
	{
		pthread_create(&tids[i], NULL, empty, NULL);
	}
	for (int i = 0; i < NUM_THREAD; i++)
	{
		pthread_join(tids[i], NULL);
	}
}

void	bench_mutex(void)
{
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mtx);
	pthread_mutex_unlock(&mtx);
}

void	bench_gettimeofday(void)
{
	struct timeval	now;

	for (int i = 0; i < NUM_THREAD; i++)
	{
		gettimeofday(&now, NULL);
	}
}

void	bench_gettimestamp(void)
{
	for (int i = 0; i < NUM_THREAD; i++)
	{
		get_timestamp_ms();
	}
}

void	bench_printf(void)
{
	for (int i = 0; i < NUM_THREAD; i++)
	{
		printf("Hello World!\n");
	}
}

void	bench_printf_spec(void)
{
	for (int i = 0; i < NUM_THREAD; i++)
	{
		printf("100 Hello World\n");
		//printf("%3d %s\n", 100, "Hello World");
	}
}

void	bench_logger(void)
{
	for (int i = 0; i < NUM_THREAD; i++)
	{
		logger("Hello World!\n");
	}
}

int	main(void)
{
	measure("bench_printf", bench_printf);
	measure("bench_printf_spec", bench_printf_spec);
	measure("bench_logger", bench_logger);
	measure("bench_gettimeofday", bench_gettimeofday);
	measure("bench_gettimestamp", bench_gettimestamp);
	measure("bench_mutex", bench_mutex);
	measure("bench_pthread_create_join", bench_pthread_create_join);
	return (0);
}
