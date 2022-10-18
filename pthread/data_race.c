/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_race.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:05:19 by susami            #+#    #+#             */
/*   Updated: 2022/10/17 18:11:52 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

int	account_a = 100;
int	account_b = 0;
int	faucet = 10000000;

void	*racyFunc(void *arg)
{
	(void)arg;
	while (faucet > 0)
	{
		if (account_a >= 10)
		{
			account_a -= 10;
			account_b += 10;
		}
		else
		{
			faucet -= 100;
			account_a += 100;
		}
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	t1, t2, t3;

	pthread_create(&t1, NULL, racyFunc, NULL);
	pthread_create(&t2, NULL, racyFunc, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("a: %d, b: %d, faucet: %d\n", account_a, account_b, faucet);
	return (0);
}
