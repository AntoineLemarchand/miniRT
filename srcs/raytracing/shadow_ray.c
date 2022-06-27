/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:51:40 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/27 11:30:09 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_obstructed(t_ray *ray, t_scene *scene, t_objs *obj)
{
	(void)ray;
	(void)scene;
	(void)obj;
	return (0);
}

static double	*get_light_ratio(t_vec *point, t_objs *obj, t_scene *scene)
{
	double	*ret;
	t_ray	ray;
	int		hit;

	ret = malloc(3 * sizeof(double));
	if (!ret)
		return (NULL);
	new_vec(point->x, point->y, point->z, &ray.origin);
	new_vec(scene->light->position.x, scene->light->position.y,
		scene->light->position.z, &ray.offset);
	vec_normalize(&ray.offset);
	hit = !is_obstructed(&ray, scene, obj);
	ret[0] = scene->light->col[0] * scene->light->ratio * hit;
	ret[1] = scene->light->col[1] * scene->light->ratio * hit;
	ret[2] = scene->light->col[2] * scene->light->ratio * hit;
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
	ratio = get_light_ratio(&point, obj, scene);
	ratio[0] = ratio[0] + scene->ambient->col[0] * scene->ambient->ratio;
	ratio[1] = ratio[1] + scene->ambient->col[1] * scene->ambient->ratio;
	ratio[2] = ratio[2] + scene->ambient->col[2] * scene->ambient->ratio;
	if (!ratio)
		return (-1);
	col = get_shape_col(obj, ratio);
	free(ratio);
	return (col);
}
