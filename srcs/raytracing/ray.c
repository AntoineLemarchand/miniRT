/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:13:09 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/02 12:23:11 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	get_dist(t_ray *ray, t_objs *shape)
{
	if (shape->type == light)
		return (-1);
	else if (shape->type == sphere)
		return (get_sphere_dist(ray, (t_sphere *)shape->val));
	else if (shape->type == plane)
		return (-1);
	else if (shape->type == cylinder)
		return (-1);
	return (-1);
}

t_objs	*shape_hit(t_ray *ray, t_scene *scene)
{
	t_objs	*ret;
	t_objs	*curr;
	float	curr_dist;
	float	min_dist;

	min_dist = -1.;
	ret = NULL;
	curr = scene->shapes;
	while (curr)
	{
		curr_dist = get_dist(ray, curr);
		if (curr_dist >= 0
			&& ((curr_dist > min_dist && min_dist >= 0) || min_dist < 0))
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

	shape = shape_hit(ray, scene);
	if (!shape)
		return (0);
	if (shape->type == sphere)
		return (get_col(((t_sphere *)(shape->val))->col[0],
			((t_sphere *)(shape->val))->col[1],
				((t_sphere *)(shape->val))->col[2]));
	else if (shape->type == plane)
		return (get_col(((t_plane *)(shape->val))->col[0],
			((t_plane *)(shape->val))->col[1],
				((t_plane *)(shape->val))->col[2]));
	else if (shape->type == cylinder)
		return (get_col(((t_cylinder *)(shape->val))->col[0],
			((t_cylinder *)(shape->val))->col[1],
				((t_cylinder *)(shape->val))->col[2]));
	return (0);
}

// Law of sines
t_ray	*init_ray(t_camera *camera, int x, int y)
{
	t_ray	*ret;
	float	angle;

	angle = camera->fov / 2;
	ret = malloc(sizeof(t_ray));
	if (!ret)
		return (NULL);
	ret->origin.x = camera->position.x;
	ret->origin.y = camera->position.y;
	ret->origin.z = camera->position.z;
	ret->offset.x = camera->orientation.x + (x - RES_X / 2);
	ret->offset.y = camera->orientation.y - (y - RES_Y / 2);;
	ret->offset.z = (sinf(90 - angle) * RES_X / 2) / sinf(angle);
	vec_normalize(&ret->offset);
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
