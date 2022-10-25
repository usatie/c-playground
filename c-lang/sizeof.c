/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizeof.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:40:08 by susami            #+#    #+#             */
/*   Updated: 2022/10/18 15:42:43 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	int	a;
	int	b[100];
	int	*c;

	c = malloc(sizeof(int) * 50);
	printf("sizeof(a) = %lu\n", sizeof(a));
	printf("sizeof(b) = %lu\n", sizeof(b));
	printf("sizeof(c) = %lu\n", sizeof(c));
	printf("sizeof(*b) = %lu\n", sizeof(*b));
	printf("sizeof(*c) = %lu\n", sizeof(*c));
}
