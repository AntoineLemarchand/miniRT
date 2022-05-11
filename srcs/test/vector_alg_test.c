/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_alg_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:08:31 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/11 14:05:02 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "miniRT.h"

int	test_vec_normalize( void )
{
	t_vec	vec;
	float	v1;
	float	v2;
	float	v3;

	v1 = -4;
	v2 = 2;
	v3 = 4;
	vec.x = v1;
	vec.y = v2;
	vec.z = v3;
	write(1, "test_vec_norm: ", 15);
	vec_normalize(&vec);
	if (almost_equal(vec.x, -0.66f, .01) && almost_equal(vec.y, 0.33f, .01)
		&& almost_equal(vec.z, 0.66f, .01))
		return (1);
	return (0);
}

int	test_vec_dot_product( void )
{
	t_vec	vec1;
	t_vec	vec2;

	vec1.x = -1;
	vec1.y = -2;
	vec1.z = 3;
	vec2.x = 4;
	vec2.y = 0;
	vec2.z = -8;
	write(1, "test_vec_dprd: ", 15);
	if (almost_equal(vec_dot_product(&vec1, &vec2), -28, .01))
		return (1);
	return (0);
}

int	test_vec_cross_product( void )
{
	t_vec	vec1;
	t_vec	vec2;
	t_vec	*cprod;

	vec1.x = -1;
	vec1.y = -2;
	vec1.z = 3;
	vec2.x = 4;
	vec2.y = 0;
	vec2.z = -8;
	write(1, "test_vec_cprd: ", 15);
	cprod = vec_cross_product(&vec1, &vec2);
	if (almost_equal(cprod->x, 16, .01) && almost_equal(cprod->y, 4, .01)
		&& almost_equal(cprod->z, 8, .01))
	{
		free(cprod);
		return (1);
	}
	free(cprod);
	return (0);
}
