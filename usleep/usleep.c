/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:23:27 by susami            #+#    #+#             */
/*   Updated: 2022/10/17 15:49:01 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

#define ONE_SEC_IN_USEC 1000000

int	main(void)
{
	struct timeval	start;
	struct timeval	end;
	int				elapsed;

	gettimeofday(&start, NULL);
	usleep(1000000);
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - start.tv_sec) * ONE_SEC_IN_USEC;
	elapsed += end.tv_usec - start.tv_usec;
	printf("timestamp : %ld.%d\n", start.tv_sec, start.tv_usec);
	printf("timestamp : %ld.%d\n", end.tv_sec, end.tv_usec);
	printf("elapsed %d usec\n", elapsed);
}
