/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:51:40 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/12 16:45:20 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	get_normal(t_vec *ret, t_objs *obj, t_vec *point, t_camera *cam)
{
	t_vec	t[2];

	if (obj->type == sphere)
		vec_reduce(point, &((t_sphere *)obj->val)->position, ret);
	else if (obj->type == plane)
		new_vec(((t_plane *)obj->val)->orientation.x,
			((t_plane *)obj->val)->orientation.y,
			((t_plane *)obj->val)->orientation.z, ret);
	else if (obj->type == triangle)
		new_vec(((t_triangle *)obj->val)->orientation.x,
			((t_triangle *)obj->val)->orientation.y,
			((t_triangle *)obj->val)->orientation.z, ret);
	else if (obj->type == cylinder)
	{
		vec_reduce(point, &((t_cylinder *)obj->val)->position, &t[1]);
		vec_cross_product(&((t_cylinder *)obj->val)->orientation, &t[1], &t[0]);
		vec_cross_product(&t[0], &((t_cylinder *)obj->val)->orientation, ret);
	}
	vec_reduce(point, &cam->position, &t[1]);
	if (vec_same_dir(&t[1], ret))
		vec_multiply(ret, -1);
}

static double	bake_shape(t_camera *cam, t_objs *obj, t_vec *point,
	t_light *light)
{
	t_vec	center;
	t_vec	normal;
	t_vec	tmp[2];
	double	dist;
	double	ret;

	ret = 0;
	get_normal(&normal, obj, point, cam);
	new_vec(light->position.x - point->x, light->position.y
		- point->y, light->position.z - point->z, &center);
	dist = vec_dot_product(&normal, &center);
	if (dist > 0)
		ret += light->ratio * dist
			/ ((vec_len(&normal)) * vec_len(&center));
	vec_reduce(&cam->position, point, &tmp[0]);
	new_vec(2 * dist * normal.x - center.x, 2 * dist * normal.y - center.y,
		2 * dist * normal.z - center.z, &tmp[1]);
	dist = vec_dot_product(&tmp[0], &tmp[1]);
	if (dist > 0 && vec_same_dir(&tmp[0], &center))
		ret += light->ratio
			* powf(dist / (vec_len(&tmp[0]) * vec_len(&tmp[1])), 10.);
	return (ret);
}

static void	get_light_ratio(t_vec *point, t_scene *scene, t_objs *obj,
		t_vec *ret)
{
	double	ratio;
	t_ray	ray;
	t_objs	*light;

	new_vec(0, 0, 0, ret);
	ratio = 0;
	light = scene->lights;
	while (light)
	{
		new_vec(((t_light *)light->val)->position.x - point->x,
			((t_light *)light->val)->position.y - point->y,
			((t_light *)light->val)->position.z - point->z, &ray.offset);
		new_vec(point->x + ray.offset.x * 0.01, point->y + ray.offset.y * 0.01,
			point->z + ray.offset.z * 0.01, &ray.origin);
		ratio = bake_shape(scene->cam, obj, point, light->val)
			* (shape_hit(&ray, scene, 0.00001, 1) == NULL);
		ret->x += ((t_light *)light->val)->col[0]
			* ((t_light *)light->val)->ratio * ratio;
		ret->y += ((t_light *)light->val)->col[1]
			* ((t_light *)light->val)->ratio * ratio;
		ret->z += ((t_light *)light->val)->col[2]
			* ((t_light *)light->val)->ratio * ratio;
		light = light->next;
	}
}

static int	get_shape_col(t_objs *obj, t_vec *ratio)
{
	t_vec	col;

	if (obj->type == sphere)
		new_vec(((t_sphere *)(obj->val))->col[0] * ratio->x / 255,
			((t_sphere *)(obj->val))->col[1] * ratio->y / 255,
			((t_sphere *)(obj->val))->col[2] * ratio->z / 255, &col);
	else if (obj->type == plane)
		new_vec(((t_plane *)(obj->val))->col[0] * ratio->x / 255,
			((t_plane *)(obj->val))->col[1] * ratio->y / 255,
			((t_plane *)(obj->val))->col[2] * ratio->z / 255, &col);
	else if (obj->type == triangle)
		new_vec(((t_triangle *)(obj->val))->col[0] * ratio->x / 255,
			((t_triangle *)(obj->val))->col[1] * ratio->y / 255,
			((t_triangle *)(obj->val))->col[2] * ratio->z / 255, &col);
	else if (obj->type == cylinder)
		new_vec(((t_cylinder *)(obj->val))->col[0] * ratio->x / 255,
			((t_cylinder *)(obj->val))->col[1] * ratio->y / 255,
			((t_cylinder *)(obj->val))->col[2] * ratio->z / 255, &col);
	else
		return (0);
	return (get_col(col.x, col.y, col.z));
}

int	get_shaded_col(t_objs *obj, t_ray *ray, t_scene *scene)
{
	t_vec	point;
	t_vec	ratio;
	double	dist;
	int		col;

	if (!obj)
		return (0);
	dist = get_dist(ray, obj);
	new_vec(ray->origin.x + ray->offset.x * dist,
		ray->origin.y + ray->offset.y * dist,
		ray->origin.z + ray->offset.z * dist, &point);
	get_light_ratio(&point, scene, obj, &ratio);
	ratio.x += scene->ambient->col[0] * scene->ambient->ratio;
	ratio.y += scene->ambient->col[1] * scene->ambient->ratio;
	ratio.z += scene->ambient->col[2] * scene->ambient->ratio;
	col = get_shape_col(obj, &ratio);
	return (col);
}
