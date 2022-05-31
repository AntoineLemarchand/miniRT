/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:59:16 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/19 15:15:59 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	*new_vec(float x, float y, float z)
{
	t_vec	*ret;

	ret = malloc(sizeof(t_vec));
	if (!ret)
		return (NULL);
	ret->x = x;
	ret->y = y;
	ret->z = z;
	return (ret);
}

void	vec_multiply(t_vec *vec, float f)
{
	if (vec)
	{
		vec->x *= f;
		vec->y *= f;
		vec->z *= f;
	}
}

void	vec_divide(t_vec *vec, float f)
{
	if (vec)
	{
		vec->x /= f;
		vec->y /= f;
		vec->z /= f;
	}
}

t_vec	*vec_reduce(t_vec *v1, t_vec *v2)
{
	t_vec *ret;

	ret = malloc(sizeof(t_vec));
	if (!ret)
		return (NULL);
	ret->x = v1->x - v2->x;
	ret->y = v1->y - v2->y;
	ret->z = v1->z - v2->z;
	return (ret);
}
