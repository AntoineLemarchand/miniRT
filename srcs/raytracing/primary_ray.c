/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:13:09 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/06 15:02:27 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	get_dist(t_ray *ray, t_objs *shape)
{
	if (shape->type == sphere)
		return (get_sphere_dist(ray, (t_sphere *)shape->val));
	else if (shape->type == plane)
		return (get_plane_dist(ray, (t_plane *)shape->val));
	else if (shape->type == cylinder)
		return (-1);
	return (-1);
}

t_objs	*shape_hit(t_ray *ray, t_scene *scene)
{
	t_objs	*ret;
	t_objs	*curr;
	double	curr_dist;
	double	min_dist;

	min_dist = -1.;
	ret = NULL;
	curr = scene->shapes;
	while (curr)
	{
		curr_dist = get_dist(ray, curr);
		if (curr_dist >= 0
			&& ((curr_dist < min_dist && min_dist >= 0) || min_dist < 0))
		{
			min_dist = curr_dist;
			ret = curr;
		}
		curr = curr->next;
	}
	return (ret);
}

// this is going to need a bit more work using light attenuation
// https://www.cs.utexas.edu/~theshark/courses/cs354/lectures/cs354-4.pdf
// slide 53
int	compute_primary_ray(t_ray *ray, t_scene *scene)
{
	t_objs	*shape;
	int		*ambient;

	ambient = scene->ambient->col;
	shape = shape_hit(ray, scene);
	if (!shape)
		return (0);
	if (shape->type == sphere)
		return (get_col((((t_sphere *)(shape->val))->col[0] * ambient[0]) / 255,
			(((t_sphere *)(shape->val))->col[1] * ambient[1]) / 255,
				(((t_sphere *)(shape->val))->col[2] * ambient[2]) / 255));
	else if (shape->type == plane)
		return (get_col((((t_plane *)(shape->val))->col[0] * ambient[0]) / 255,
			(((t_plane *)(shape->val))->col[1] * ambient[1]) / 255,
				(((t_plane *)(shape->val))->col[2] * ambient[2]) / 255));
	else if (shape->type == cylinder)
		return (get_col(((t_cylinder *)(shape->val))->col[0] * ambient[0] / 255,
			((t_cylinder *)(shape->val))->col[1] * ambient[1] / 255,
				((t_cylinder *)(shape->val))->col[2] * ambient[2] /255));
	return (0);
}

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

void	get_ray_dir(t_vec *matrix, t_camera *camera, int x, int y, t_vec *ret)
{
	float	focal_dist;

	focal_dist = (180 - camera->fov + 1) * (RES_X / 2) / 180;
	ret->x = matrix[0].x * (x - RES_X / 2) - matrix[1].x * (y - RES_Y / 2)
		+ matrix[2].x * focal_dist;
	ret->y = matrix[0].y * (x - RES_X / 2) - matrix[1].y * (y - RES_Y / 2)
		+ matrix[2].y * focal_dist;
	ret->z = matrix[0].z * (x - RES_X / 2) - matrix[1].z * (y - RES_Y / 2)
		+ matrix[2].z * focal_dist;
	vec_normalize(ret);
}

// Law of sines for distance to viewport
t_ray	*init_ray(t_camera *camera, int x, int y)
{
	t_ray	*ret;
	t_vec	*cam_to_world;

	ret = malloc(sizeof(t_ray));
	if (!ret)
		return (NULL);
	cam_to_world = compute_cam(camera);
	if (!cam_to_world)
		free(ret);
	if (!cam_to_world)
		return (NULL);
	ret->origin.x = camera->position.x;
	ret->origin.y = camera->position.y;
	ret->origin.z = camera->position.z;
	get_ray_dir(cam_to_world, camera, x, y, &ret->offset);
	free(cam_to_world);
	return (ret);
}

int	compute_rays(t_scene *scene, t_data *data)
{
	int		y;
	int		x;
	t_ray	*ray;

	y = 0;
	while (y < RES_Y)
	{
		x = 0;
		while (x < RES_X)
		{
			ray = init_ray(scene->cam, x, y);
			if (!ray)
				return (1);
			ft_mlx_pixel_put(data, x, y,
				compute_primary_ray(ray, scene));
			free(ray);
			x++;
		}
		y++;
		printf("\r%i / %i | %i / %i", x, RES_X, y, RES_Y);
	}
	printf("\nRaycasting done\n");
	return (0);
}
