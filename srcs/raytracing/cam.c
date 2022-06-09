/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:44:20 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/09 11:09:50 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// https://www.scratchapixel.com/lessons/
// mathematics-physics-for-computer-graphics/lookat-function
t_vec	*compute_cam(t_camera *camera)
{
	t_vec	*cam_to_world;
	t_vec	arbitrary;

	cam_to_world = malloc(3 * sizeof(t_vec));
	new_vec(camera->orientation.x, camera->orientation.y, camera->orientation.z,
		&cam_to_world[2]);
	vec_normalize(&cam_to_world[2]);
	new_vec(0, 1, 0, &arbitrary);
	vec_normalize(&arbitrary);
	vec_cross_product(&arbitrary, &cam_to_world[2], &cam_to_world[0]);
	vec_cross_product(&cam_to_world[2], &cam_to_world[0], &cam_to_world[1]);
	return (cam_to_world);
}

void	build_ray(t_ray *ray)
{
	t_vec	matrix[3];
	t_vec	arbitrary;

	new_vec(ray->offset.x, ray->offset.y, ray->offset.z, &matrix[2]);
	vec_normalize(&matrix[2]);
	new_vec(0, 1, 0, &arbitrary);
	vec_normalize(&arbitrary);
	vec_cross_product(&arbitrary, &matrix[2], &matrix[0]);
	vec_cross_product(&matrix[2], &matrix[0], &matrix[1]);
	ray->offset.x = matrix[0].x + matrix[1].x - matrix[2].x;
	ray->offset.y = matrix[0].y + matrix[1].y - matrix[2].y;
	ray->offset.z = matrix[0].z + matrix[1].z - matrix[2].z;
	vec_normalize(&ray->offset);
}

// Law of sines for distance to viewport
t_ray	*init_ray(t_camera *camera, t_vec *matrix, int x, int y)
{
	t_ray	*ret;
	float	focal_dist;

	ret = malloc(sizeof(t_ray));
	if (!ret)
		return (NULL);
	ret->origin.x = camera->position.x;
	ret->origin.y = camera->position.y;
	ret->origin.z = camera->position.z;
	focal_dist = (180 - camera->fov + 1) * (RES_X / 2) / 180;
	ret->offset.x = matrix[0].x * (x - RES_X / 2)
		- matrix[1].x * (y - RES_Y / 2) + matrix[2].x * focal_dist;
	ret->offset.y = matrix[0].y * (x - RES_X / 2)
		- matrix[1].y * (y - RES_Y / 2) + matrix[2].y * focal_dist;
	ret->offset.z = matrix[0].z * (x - RES_X / 2)
		- matrix[1].z * (y - RES_Y / 2) + matrix[2].z * focal_dist;
	vec_normalize(&ret->offset);
	return (ret);
}
