/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:04:13 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/27 13:35:45 by alemarch         ###   ########.fr       */
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
	double	ret;
	t_vec	center;

	center.x = plane->position.x - ray->origin.x;
	center.y = plane->position.y - ray->origin.y;
	center.z = plane->position.z - ray->origin.z;
	ret = vec_dot_product(&plane->orientation, &center) /
		vec_dot_product(&plane->orientation, &ray->offset);
	return (ret);
}

double    get_cylinder_dist(t_ray *ray, t_cylinder *cylinder)
{
    t_vec    center;
    t_vec    direction;
    t_vec    cross_prod[2];
    double    quad[3];
    double    discr;
    double    ret[2];
    double    radius;

    radius = cylinder->diameter / 2;
    center.x = ray->origin.x - cylinder->position.x;
    center.y = ray->origin.y - cylinder->position.y;
    center.z = ray->origin.z - cylinder->position.z;
    direction = cylinder->orientation;
    vec_normalize(&direction);
    vec_cross_product(&direction, &center, &cross_prod[0]);
    vec_cross_product(&direction, &ray->offset, &cross_prod[1]);
    quad[0] = vec_dot_product(&cross_prod[1], &cross_prod[1]);
    quad[1] = 2 * vec_dot_product(&cross_prod[0], &cross_prod[1]);
    quad[2] = vec_dot_product(&cross_prod[0], &cross_prod[0]) - radius * radius;
    discr = quad[1] * quad[1] - 4 * quad[0] * quad[2];
    if (discr < 0)
        return (-1);
    ret[0] = (-quad[1] + sqrtf(discr)) / (2 * quad[0]);
    ret[1] = (-quad[1] - sqrtf(discr)) / (2 * quad[0]);
	if (fabs(ret[0]) >= fabs((cylinder->height / 2 - vec_dot_product(&direction, &center)) / vec_dot_product(&direction, &ray->offset)))
		ret[0] = -1;
	if (fabs(ret[1]) >= fabs((cylinder->height / 2 - vec_dot_product(&direction, &center)) / vec_dot_product(&direction, &ray->offset)))
		ret[1] = -1;
    return (return_dist(ret));
}
