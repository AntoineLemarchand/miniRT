/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:51:40 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/08 11:34:08 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	*get_light_ratio(t_vec point, t_objs *obj, t_scene *scene)
{
	double	*ret;

	(void)point;
	(void)obj;
	(void)scene;
	ret = malloc(3 * sizeof(double));
	if (!ret)
		return (NULL);
	ret[0] = 255;
	ret[1] = 255;
	ret[2] = 255;
	return (ret);
}

static int	get_shape_col(t_objs *obj, t_scene *scene, double *ratio)
{
	int	*ambient;

	ambient = scene->ambient->col;
	ratio[0] = ratio[0] * ambient[0] / 255;
	ratio[1] = ratio[1] * ambient[1] / 255;
	ratio[2] = ratio[2] * ambient[2] / 255;
	if (obj->type == sphere)
		return (get_col((((t_sphere *)(obj->val))->col[0] * ratio[0]) / 255,
			(((t_sphere *)(obj->val))->col[1] * ratio[1]) / 255,
				(((t_sphere *)(obj->val))->col[2] * ratio[2]) / 255));
	else if (obj->type == plane)
		return (get_col((((t_plane *)(obj->val))->col[0] * ratio[0]) / 255,
			(((t_plane *)(obj->val))->col[1] * ratio[1]) / 255,
				(((t_plane *)(obj->val))->col[2] * ratio[2]) / 255));
	else if (obj->type == cylinder)
		return (get_col(((t_cylinder *)(obj->val))->col[0] * ratio[0] / 255,
			((t_cylinder *)(obj->val))->col[1] * ratio[1] / 255,
				((t_cylinder *)(obj->val))->col[2] * ratio[2] / 255));
	return (0);
}

int	get_shaded_col(t_objs *obj, t_ray *ray, t_scene *scene)
{
	t_vec	point;
	double	*ratio;

	if (!obj)
		return (0);
	new_vec(ray->origin.x + ray->offset.x * get_dist(ray, obj),
		ray->origin.y + ray->offset.y * get_dist(ray, obj),
		ray->origin.z + ray->offset.z * get_dist(ray, obj),
		&point);
	ratio = get_light_ratio(point, obj, scene);
	if (!ratio)
		return (-1);
	return (get_shape_col(obj, scene, ratio));
}
