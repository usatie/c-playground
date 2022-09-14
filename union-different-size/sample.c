/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:23:54 by susami            #+#    #+#             */
/*   Updated: 2022/09/14 10:47:10 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>

union u {
	uint32_t	i;

	struct s1 {
		uint8_t	a;
		uint8_t	b;
		uint8_t	c;
		uint8_t	d;
	} v1;

	struct s2 {
		uint8_t	e;
		uint8_t	f;
	} v2;

	struct s3 {
		uint8_t	g;
	} v3;
};

void	print_u(union u u)
{
	printf("-----------------------\n");
	printf("i: {%u}\n", u.i);
	printf("v1: {%u, %u, %u, %u}\n", u.v1.a, u.v1.b, u.v1.c, u.v1.d);
	printf("v2: {%u, %u}\n", u.v2.e, u.v2.f);
	printf("v3: {%u}\n", u.v3.g);
}

int	main(void)
{
	union u u;

	u.i = 1;
	print_u(u);

	u.i = 255;
	print_u(u);

	u.i = 256;
	print_u(u);

	u.v1 = (struct s1){255, 255, 255, 255};
	print_u(u);
}
