/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:04:13 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/10 15:31:20 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//https://www.gabrielgambetta.com/
double	get_sphere_dist(t_ray *ray, t_sphere *sphere)
{
	t_vec	center;
	double	quad[3];
	double	discr;
	double	ret[2];
	double	radius;

	radius = sphere->diameter / 2;
	center.x = ray->origin.x - sphere->position.x;
	center.y = ray->origin.y - sphere->position.y;
	center.z = ray->origin.z - sphere->position.z;
	quad[0] = vec_dot_product(&ray->offset, &ray->offset);
	quad[1] = 2 * vec_dot_product(&center, &ray->offset);
	quad[2] = vec_dot_product(&center, &center) - radius * radius;
	discr = quad[1] * quad[1] - 4 * quad[0] * quad[2];
	if (discr < 0)
		return (-1);
	ret[0] = (-quad[1] + sqrtf(discr)) / (2 * quad[0]);
	ret[1] = (-quad[1] - sqrtf(discr)) / (2 * quad[0]);
	if (ret[0] < 0)
	{
		if (ret[1] < 0)
			return (-1);
		return (ret[1]);
	}
	return (fmin(ret[0], ret[1]));
}

double	get_plane_dist(t_ray *ray, t_plane *plane)
{
	double	denom;
	double	ret;
	t_vec	center;

	denom = vec_dot_product(&plane->orientation, &ray->offset);
	center.x = plane->position.x - ray->origin.x;
	center.y = plane->position.y - ray->origin.y;
	center.z = plane->position.z - ray->origin.z;
	if (fabs(denom) > 0.00001)
	{
		ret = vec_dot_product(&center, &plane->orientation) / denom;
		if (ret >= 0)
			return (ret);
	}
	return (-1);
}

double	get_cylinder_dist(t_ray *ray, t_cylinder *cylinder)
{
	t_vec	center;
	double	quad[3];
	double	discr;
	double	ret[2];
	double	radius;

	radius = cylinder->diameter / 2;
	center.x = ray->origin.x - cylinder->position.x;
	center.y = ray->origin.y - cylinder->position.y;
	center.z = ray->origin.z - cylinder->position.z;
	t_vec *matrix = build_ray_matrix(&cylinder->orientation);
	t_vec newoffset;
	newoffset.x = ray->offset.x * matrix[0].x + ray->offset.y * matrix[0].y + ray->offset.z * matrix[0].z;
	newoffset.y = ray->offset.x * matrix[1].x + ray->offset.y * matrix[1].y + ray->offset.z * matrix[1].z;
	newoffset.z = ray->offset.x * matrix[2].x + ray->offset.y * matrix[2].y + ray->offset.z * matrix[2].z;
	vec_normalize(&newoffset);
	quad[0] = powf(newoffset.x, 2.) + powf(newoffset.y, 2.);
	quad[1] = 2 * center.x * (newoffset.x) + 2 * center.y * (newoffset.y);
	quad[2] = powf(center.x, 2.) + powf(center.y, 2.) - radius * radius;
	discr = quad[1] * quad[1] - 4 * quad[0] * quad[2];
	if (discr < 0)
		return (-1);
	ret[0] = (-quad[1] + sqrtf(discr)) / (2 * quad[0]);
	ret[1] = (-quad[1] - sqrtf(discr)) / (2 * quad[0]);
	if (ret[0] < 0)
	{
		if (ret[1] < 0)
			return (-1);
		return (ret[1]);
	}
	return (fmin(ret[0], ret[1]));
}
