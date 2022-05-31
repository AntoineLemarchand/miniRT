/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:13:09 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/25 12:18:18 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	get_sphere_dist(t_ray *ray, t_sphere *sphere)
{
	float	ret[2];
	float	tm;
	float	lm2;

	ret[0] = ((b * -1) + sqrtf(b * b - 4 * a * c)) / (2 * a);
	ret[1] = ((b * -1) - sqrtf(b * b - 4 * a * c)) / (2 * a);
	printf("%f, %f\n", ret[0], ret[1]);
	if (ret[0] < 0 && ret[1] < 0)
		return (-1);
	else if (ret[0] < 0)
		return (ret[1]);
	else if (ret[1] < 0)
		return (ret[0]);
	else
		if (ret[0] < ret[1])
			return (ret[0]);
	return (ret[1]);
}

float	get_dist(t_ray *ray, t_objs *shape)
{
	if (shape->type == LIGHT)
		return (-1);
	else if (shape->type == SPHERE)
		return (get_sphere_dist(ray, (t_sphere*)shape->val));
	else if (shape->type == PLANE)
		return (-1);
	else if (shape->type == CYLINDER)
		return (-1);
	return (-1.);
}

t_objs	*shape_hit(t_ray *ray, t_scene *scene)
{
	t_objs	*ret;
	float	curr_dist;
	float	min_dist;

	min_dist = -1.;
	ret = NULL;
	if (!ray || !scene)
		return (NULL);
	while (scene->shapes)
	{
		curr_dist = get_dist(ray, scene->shapes);
		printf("%i %f\n", scene->shapes->type, curr_dist);
		if ((curr_dist < min_dist || min_dist == -1.) && curr_dist != -1)
		{
			min_dist = curr_dist;
			ret = scene->shapes;
		}
		scene->shapes = scene->shapes->next;
	}
	return (ret);
}
 
// this is going to need a bit more work using light attenuation
// https://www.cs.utexas.edu/~theshark/courses/cs354/lectures/cs354-4.pdf
// diapo 53
int	compute_primary_ray(t_ray *ray, t_scene *scene)
{
	t_objs	*shape;

	shape = shape_hit(ray, scene);
	if (!shape)
		return (0);
	if (shape->type == LIGHT)
		return (get_col(((t_light*)(shape->val))->col[0],
				((t_light*)(shape->val))->col[1],
				((t_light*)(shape->val))->col[2]));
	else if (shape->type == SPHERE)
		return (get_col(((t_sphere*)(shape->val))->col[0],
				((t_sphere*)(shape->val))->col[0],
				((t_sphere*)(shape->val))->col[2]));
	else if (shape->type == PLANE)
		return (get_col(((t_plane*)(shape->val))->col[0],
				((t_plane*)(shape->val))->col[1],
				((t_plane*)(shape->val))->col[2]));
	else if (shape->type == CYLINDER)
		return (get_col(((t_cylinder*)(shape->val))->col[0],
				((t_cylinder*)(shape->val))->col[1],
				((t_cylinder*)(shape->val))->col[2]));
	return (0);
}

t_ray	*init_ray(t_camera *camera, int x, int y)
{
	t_ray	*ret;

	ret = malloc(sizeof(t_ray));
	if (!ret)
		return (NULL);
	ret->origin.x = camera->position.x;
	ret->origin.y = camera->position.y;
	ret->origin.z = camera->position.z;
	ret->offset.x = camera->orientation.x + x;
	ret->offset.y = camera->orientation.y + y;
	ret->offset.y = camera->orientation.z + camera->fov;
//	vec_normalize(&ret->offset);
	return (ret);
}

int	*compute_rays(t_scene *scene)
{
	int		y;
	int		x;
	t_ray	*ray;
	int		*computed_rays;


	y = 0;
	computed_rays = malloc(sizeof(int) * (RES_X * RES_Y));
	if (!computed_rays)
		return (NULL);
	while (y < RES_Y)
	{
		x = 0;
		while(x < RES_X)
		{
			ray = init_ray(scene->cam, x, y);
			computed_rays[y * RES_X + x]
				= compute_primary_ray(ray, scene);
			free(ray);
			x++;
		}
		y++;
	}
	return(computed_rays);
}
