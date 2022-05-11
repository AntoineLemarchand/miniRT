/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:08:31 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/11 11:28:23 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "miniRT.h"

int	test_vec_init( void )
{
	t_vec	*test;
	int		ret;
	float	v1;
	float	v2;
	float	v3;

	v1 = 130.7;
	v2 = 0.;
	v3 = 42.42;
	write(1, "test_vec_init: ", 15);
	test = new_vec(v1, v2, v3);
	if (test->x == v1 && test->y == v2 && test->z == v3)
		ret = 1;
	else
		ret = 0;
	free(test);
	return (ret);
}

int	test_vec_mult( void )
{
	t_vec	test;
	int		ret;

	write(1, "test_vec_mult: ", 15);
	test.x = 1;
	test.y = 0;
	test.z = -1;
	vec_multiply(&test, 130.);
	if (test.x == 130. && test.y == 0. && test.z == -130.)
		ret = 1;
	else
		ret = 0;
	return (ret);
}

int	test_vec_divide( void )
{
	t_vec	test;
	int		ret;

	write(1, "test_vec_div:  ", 15);
	test.x = 130.;
	test.y = 0.;
	test.z = -130.;
	vec_divide(&test, 130.);
	if (test.x == 1. && test.y == 0. && test.z == -1.)
		ret = 1;
	else
		ret = 0;
	return (ret);
}
