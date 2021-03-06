/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_alg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:41:45 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/06 12:31:29 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// http://www.fundza.com/vectors/normalize/
void	vec_normalize(t_vec *vec)
{
	double	length;

	if (vec)
	{
		length = sqrtf(powf(vec->x, 2.) + powf(vec->y, 2.) + powf(vec->z, 2.));
		vec->x /= length;
		vec->y /= length;
		vec->z /= length;
	}
}

// https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
// figure 15
double	vec_dot_product(t_vec *v1, t_vec *v2)
{
	if (v1 && v2)
		return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
	return (0.);
}

// https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
// figure 20
void	vec_cross_product(t_vec *v1, t_vec *v2, t_vec *ret)
{
	if (v1 && v2)
	{
		ret->x = v1->y * v2->z - v1->z * v2->y;
		ret->y = v1->z * v2->x - v1->x * v2->z;
		ret->z = v1->x * v2->y - v1->y * v2->x;
	}
}

int	vec_equal(t_vec *v1, t_vec *v2)
{
	return (v1->x == v2->x && v1->y == v2->y && v1->z == v2->z);
}

t_vec	vec_inv(t_vec vec)
{
	t_vec	ret;

	ret = vec;
	vec_multiply(&ret, -1);
	return (ret);
}
