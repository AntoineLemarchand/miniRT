/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:04:13 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/31 14:08:18 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//https://www.gabrielgambetta.com/
float	get_sphere_dist(t_ray *ray, t_sphere *sphere)
{
	t_vec	center;
	float	quad[3];
	float	discr;
	float	ret[2];

	center.x = ray->origin.x - sphere->position.x;
	center.y = ray->origin.y - sphere->position.y;
	center.z = ray->origin.z - sphere->position.z;
	quad[0] = vec_dot_product(&ray->offset, &ray->offset);
	quad[1] = 2 * vec_dot_product(&center, &ray->offset);
	quad[2] = vec_dot_product(&center, &center)
		- powf((sphere->diameter / 2), 2.);
	discr = quad[1] * quad[1] - 4 * quad[0] * quad[2];
	if (discr < 0)
		return (-1);
	ret[0] = (-1 * quad[1] + sqrtf(discr)) / (2 * quad[0]);
	ret[1] = (-1 * quad[1] - sqrtf(discr)) / (2 * quad[0]);
	if (ret[0] < 0)
	{
		if (ret[1] < 0)
			return (-1);
		return (ret[1]);
	}
	return (ret[0]);
}
