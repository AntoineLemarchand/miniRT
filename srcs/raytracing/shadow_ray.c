/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:51:40 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/04 17:48:48 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	get_normal(t_vec *ret, t_objs *obj, t_vec *point)
{
	int		sign;

	if (obj->type == sphere)
	{
		ret->x = point->x - ((t_sphere *)obj->val)->position.x;
		ret->y = point->y - ((t_sphere *)obj->val)->position.y;
		ret->z = point->z - ((t_sphere *)obj->val)->position.z;
	}
	else if (obj->type == plane)
	{
		if (((t_plane *)obj->val)->orientation.x * point->x
			+ ((t_plane *)obj->val)->orientation.y
			* point->y + ((t_plane *)obj->val)->orientation.z * point->z > 0)
			sign = -1;
		else
			sign = 1;
		ret->x = ((t_plane *)obj->val)->orientation.x * sign;
		ret->y = ((t_plane *)obj->val)->orientation.y * sign;
		ret->z = ((t_plane *)obj->val)->orientation.z * sign;
	}
}

static double	bake_shape(t_scene *scene, t_objs *obj,
	t_vec *point)
{
	t_vec	center;
	t_vec	normal;
	double	dist;

	get_normal(&normal, obj, point);
	center.x = scene->light->position.x - point->x;
	center.y = scene->light->position.y - point->y;
	center.z = scene->light->position.z - point->z;
	dist = vec_dot_product(&normal, &center);
	if (dist > 0)
		return (scene->light->ratio * dist
			/ (vec_len(&normal) * vec_len(&center)));
	return (0);
}

static double	*get_light_ratio(t_vec *point, t_scene *scene, t_objs *obj)
{
	double	*ret;
	t_ray	ray;
	double	ratio;

	ret = malloc(3 * sizeof(double));
	if (!ret)
		return (NULL);
	new_vec(point->x, point->y, point->z, &ray.origin);
	new_vec(scene->light->position.x - point->x, scene->light->position.y
		- point->y, scene->light->position.z - point->z, &ray.offset);
	ratio = bake_shape(scene, obj, point)
		* (shape_hit(&ray, scene, 0.001, 1) == NULL);
	ret[0] = scene->light->col[0] * scene->light->ratio * ratio;
	ret[1] = scene->light->col[1] * scene->light->ratio * ratio;
	ret[2] = scene->light->col[2] * scene->light->ratio * ratio;
	return (ret);
}

static int	get_shape_col(t_objs *obj, double *ratio)
{
	t_vec	col;

	if (obj->type == sphere)
		new_vec(((t_sphere *)(obj->val))->col[0] * ratio[0] / 255,
			((t_sphere *)(obj->val))->col[1] * ratio[1] / 255,
			((t_sphere *)(obj->val))->col[2] * ratio[2] / 255, &col);
	else if (obj->type == plane)
		new_vec(((t_plane *)(obj->val))->col[0] * ratio[0] / 255,
			((t_plane *)(obj->val))->col[1] * ratio[1] / 255,
			((t_plane *)(obj->val))->col[2] * ratio[2] / 255, &col);
	else if (obj->type == cylinder)
		new_vec(((t_cylinder *)(obj->val))->col[0] * ratio[0] / 255,
			((t_cylinder *)(obj->val))->col[1] * ratio[1] / 255,
			((t_cylinder *)(obj->val))->col[2] * ratio[2] / 255, &col);
	else
		return (0);
	return (get_col(col.x, col.y, col.z));
}

int	get_shaded_col(t_objs *obj, t_ray *ray, t_scene *scene)
{
	t_vec	point;
	double	*ratio;
	double	dist;
	int		col;

	if (!obj)
		return (0);
	dist = get_dist(ray, obj);
	new_vec(ray->origin.x + ray->offset.x * dist,
		ray->origin.y + ray->offset.y * dist,
		ray->origin.z + ray->offset.z * dist, &point);
	ratio = get_light_ratio(&point, scene, obj);
	ratio[0] = ratio[0] + scene->ambient->col[0] * scene->ambient->ratio;
	ratio[1] = ratio[1] + scene->ambient->col[1] * scene->ambient->ratio;
	ratio[2] = ratio[2] + scene->ambient->col[2] * scene->ambient->ratio;
	if (!ratio)
		return (-1);
	col = get_shape_col(obj, ratio);
	free(ratio);
	return (col);
}
