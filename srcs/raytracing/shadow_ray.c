/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:51:40 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/12 16:37:10 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	get_normal(t_vec *ret, t_objs *obj, t_vec *point, t_camera *cam)
{
	t_vec	tmp1;
	t_vec	tmp2;

	if (obj->type == sphere)
		vec_reduce(point, &((t_sphere *)obj->val)->position, ret);
	else if (obj->type == plane)
	{
		ret->x = ((t_plane *)obj->val)->orientation.x;
		ret->y = ((t_plane *)obj->val)->orientation.y;
		ret->z = ((t_plane *)obj->val)->orientation.z;
	}
	else if (obj->type == cylinder)
	{
		vec_reduce(point, &((t_cylinder *)obj->val)->position, &tmp2);
		vec_cross_product(&((t_cylinder *)obj->val)->orientation, &tmp2, &tmp1);
		vec_cross_product(&tmp1, &((t_cylinder *)obj->val)->orientation, ret);
	}
	vec_reduce(point, &cam->position, &tmp1);
	if (vec_same_dir(&tmp1, ret))
		vec_multiply(ret, -1);
}

static double	bake_shape(t_scene *scene, t_objs *obj, t_vec *point)
{
	t_vec	center;
	t_vec	normal;
	double	dist;
	double	ret;

	ret = 0;
	get_normal(&normal, obj, point, scene->cam);
	new_vec(scene->light->position.x - point->x,
		scene->light->position.y - point->y,
		scene->light->position.z - point->z, &center);
	dist = vec_dot_product(&normal, &center);
	if (dist > 0)
		ret += scene->light->ratio * dist
			/ ((vec_len(&normal)) * vec_len(&center));
	return (ret);
}

static double	*get_light_ratio(t_vec *point, t_scene *scene, t_objs *obj)
{
	double	*ret;
	t_ray	ray;
	double	ratio;

	ret = malloc(3 * sizeof(double));
	if (!ret)
		return (NULL);
	new_vec(scene->light->position.x - point->x, scene->light->position.y
		- point->y, scene->light->position.z - point->z, &ray.offset);
	new_vec(point->x + ray.offset.x * 0.01, point->y + ray.offset.y * 0.01,
		point->z + ray.offset.z * 0.01, &ray.origin);
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
