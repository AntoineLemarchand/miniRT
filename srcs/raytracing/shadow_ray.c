/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:51:40 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/06 16:06:51 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_shape_col(t_objs *obj, t_scene *scene)
{
	int	*ambient;

	ambient = scene->ambient->col;
	if (obj->type == sphere)
		return (get_col((((t_sphere *)(obj->val))->col[0] * ambient[0]) / 255,
			(((t_sphere *)(obj->val))->col[1] * ambient[1]) / 255,
				(((t_sphere *)(obj->val))->col[2] * ambient[2]) / 255));
	else if (obj->type == plane)
		return (get_col((((t_plane *)(obj->val))->col[0] * ambient[0]) / 255,
			(((t_plane *)(obj->val))->col[1] * ambient[1]) / 255,
				(((t_plane *)(obj->val))->col[2] * ambient[2]) / 255));
	else if (obj->type == cylinder)
		return (get_col(((t_cylinder *)(obj->val))->col[0] * ambient[0] / 255,
			((t_cylinder *)(obj->val))->col[1] * ambient[1] / 255,
				((t_cylinder *)(obj->val))->col[2] * ambient[2] / 255));
	return (0);
}

int	get_shaded_col(t_objs *obj, t_ray *ray, t_scene *scene)
{
	(void)ray;
	if (!obj)
		return (0);
	return (get_shape_col(obj, scene));
}
