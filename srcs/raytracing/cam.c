/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:44:20 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/04 17:02:28 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// https://www.scratchapixel.com/lessons/
// mathematics-physics-for-computer-graphics/lookat-function
t_vec	*compute_cam(t_camera *camera)
{
	t_vec	*matrix;
	t_vec	arbitrary;

	matrix = malloc(3 * sizeof(t_vec));
	new_vec(camera->orientation.x, camera->orientation.y, camera->orientation.z,
		&matrix[2]);
	vec_normalize(&matrix[2]);
	new_vec(0, 1, 0, &arbitrary);
	if (camera->orientation.x == 0
		&& (camera->orientation.y == 1 || camera->orientation.y == -1)
		&& camera->orientation.z == 0)
		new_vec(0, 0, 1, &arbitrary);
	vec_normalize(&arbitrary);
	vec_cross_product(&arbitrary, &matrix[2], &matrix[0]);
	vec_cross_product(&matrix[2], &matrix[0], &matrix[1]);
	return (matrix);
}

t_vec	*build_ray_matrix(t_vec *offset, t_vec *matrix)
{
	t_vec	arbitrary;

	new_vec(offset->x, offset->y, offset->z, &matrix[2]);
	vec_normalize(&matrix[2]);
	new_vec(0, 1, 0, &arbitrary);
	vec_normalize(&arbitrary);
	vec_cross_product(&arbitrary, &matrix[2], &matrix[0]);
	vec_cross_product(&matrix[2], &matrix[0], &matrix[1]);
	return (matrix);
}

// Law of sines for distance to viewport
t_ray	*init_ray(t_camera *camera, t_vec *matrix, int x, int y)
{
	t_ray	*ret;
	float	px;
	float	py;
	float	focal_dist;

	ret = malloc(sizeof(t_ray));
	if (!ret)
		return (NULL);
	ret->origin.x = camera->position.x;
	ret->origin.y = camera->position.y;
	ret->origin.z = camera->position.z;
	px = (x - RES_X / 2);
	py = (y - RES_Y / 2);
	focal_dist = (180 - camera->fov) * (RES_X / 2) / 180;
	ret->offset.x = px * matrix[0].x - py * matrix[1].x
		+ focal_dist * matrix[2].x;
	ret->offset.y = px * matrix[0].y - py * matrix[1].y
		+ focal_dist * matrix[2].y;
	ret->offset.z = px * matrix[0].z - py * matrix[1].z
		+ focal_dist * matrix[2].z;
	vec_normalize(&ret->offset);
	return (ret);
}
