/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:59:16 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/09 15:59:40 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	*newVec(float x, float y, float z)
{
	t_vec	*ret;

	ret = malloc(sizeof(t_vec));
	if (!ret)
		return (NULL);
	ret->x = x;
	ret->y = y;
	ret->z = z;
}

void	multiply(t_vec *vec, float f)
{
	if (vec)
	{
		vec->x *= length;
		vec->y *= length;
		vec->z *= length;
	}
}

void	divide(t_vec *vec, float f)
{
	if (vec)
	{
		vec->x /= length;
		vec->y /= length;
		vec->z /= length;
	}
}
