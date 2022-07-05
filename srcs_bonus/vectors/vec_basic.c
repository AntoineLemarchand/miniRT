/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:59:16 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/05 09:56:25 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	new_vec(double x, double y, double z, t_vec *ret)
{
	ret->x = x;
	ret->y = y;
	ret->z = z;
}

void	vec_multiply(t_vec *vec, double f)
{
	if (vec)
	{
		vec->x *= f;
		vec->y *= f;
		vec->z *= f;
	}
}

void	vec_divide(t_vec *vec, double f)
{
	if (vec)
	{
		vec->x /= f;
		vec->y /= f;
		vec->z /= f;
	}
}

void	vec_reduce(t_vec *v1, t_vec *v2, t_vec *ret)
{
	ret->x = v1->x - v2->x;
	ret->y = v1->y - v2->y;
	ret->z = v1->z - v2->z;
}

double	vec_len(t_vec *vec)
{
	return (sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}
