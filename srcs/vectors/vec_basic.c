/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:59:16 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/10 09:54:18 by alemarch         ###   ########.fr       */
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

void	multiply(t_vec *vec, float f)
{
	if (vec)
	{
		vec->x *= f;
		vec->y *= f;
		vec->z *= f;
	}
}

void	divide(t_vec *vec, float f)
{
	if (vec)
	{
		vec->x /= f;
		vec->y /= f;
		vec->z /= f;
	}
}
