/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:04:13 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/10 16:48:26 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	return_dist(double *ret)
{
	if (ret[0] < 0)
	{
		if (ret[1] < 0)
			return (-1);
		return (ret[1]);
	}
	return (fmin(ret[0], ret[1]));
}

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
	return (return_dist(ret));
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

static void	cylinder_base_change(t_ray *ray, t_vec *matrix)
{
	t_vec	orig;
	t_vec	offs;

	new_vec(ray->origin.x, ray->origin.y, ray->origin.z, &orig);
	ray->origin.x = orig.x * matrix[0].x + orig.y * matrix[0].y
		- orig.z * matrix[0].z;
	ray->origin.y = orig.x * matrix[1].x + orig.y * matrix[1].y
		- orig.z * matrix[1].z;
	ray->origin.z = orig.x * matrix[2].x + orig.y * matrix[2].y
		- orig.z * matrix[2].z;
	new_vec(ray->offset.x, ray->offset.y, ray->offset.z, &offs);
	ray->offset.x = offs.x * matrix[0].x + offs.y * matrix[0].y
		- offs.z * matrix[0].z;
	ray->offset.y = offs.x * matrix[1].x + offs.y * matrix[1].y
		- offs.z * matrix[1].z;
	ray->offset.z = offs.x * matrix[2].x + offs.y * matrix[2].y
		- offs.z * matrix[2].z;
	vec_normalize(&ray->offset);
}

double	get_cylinder_dist(t_ray *ray, t_cylinder *cylinder)
{
	t_ray	cyl;
	double	quad[3];
	double	discr;
	double	ret[2];
	t_vec	matrix;

	build_ray_matrix(&cylinder->orientation, &matrix);
	new_vec(ray->origin.x - cylinder->position.x, ray->origin.y
		- cylinder->position.y, ray->origin.z - cylinder->position.z,
		&cyl.origin);
	new_vec(ray->offset.x, ray->offset.y, ray->offset.z, &cyl.offset);
	cylinder_base_change(&cyl, &matrix);
	quad[0] = powf(cyl.offset.x, 2.) + powf(cyl.offset.y, 2.);
	quad[1] = 2 * cyl.origin.x * cyl.offset.x + 2 * cyl.origin.y * cyl.offset.y;
	quad[2] = powf(cyl.origin.x, 2.) + powf(cyl.origin.y, 2.)
		- cylinder->diameter / 2;
	discr = quad[1] * quad[1] - 4 * quad[0] * quad[2];
	if (discr < 0)
		return (-1);
	ret[0] = (-quad[1] + sqrtf(discr)) / (2 * quad[0]);
	ret[1] = (-quad[1] - sqrtf(discr)) / (2 * quad[0]);
	return (return_dist(ret));
}
