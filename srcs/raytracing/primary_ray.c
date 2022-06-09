/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:13:09 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/09 11:15:49 by alemarch         ###   ########.fr       */
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

t_objs	*shape_hit(t_ray *ray, t_scene *scene, t_objs *ignore)
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
		if (curr != ignore && (curr_dist >= 0
				&& ((curr_dist < min_dist && min_dist >= 0) || min_dist < 0)))
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

	shape = shape_hit(ray, scene, NULL);
	return (get_shaded_col(shape, ray, scene));
}

int	compute_rays(t_scene *scene, t_data *data, t_ray *ray, t_vec *matrix)
{
	int		coord[2];
	int		col;

	coord[0] = -1;
	matrix = compute_cam(scene->cam);
	if (!matrix)
		return (1);
	while (++coord[0] < RES_Y)
	{
		coord[1] = -1;
		while (++coord[1] < RES_X)
		{
			ray = init_ray(scene->cam, matrix, coord[1], coord[0]);
			if (ray)
				col = compute_primary_ray(ray, scene);
			free(ray);
			if (!ray || col == -1)
				free(matrix);
			if (!ray || col == -1)
				return (1);
			ft_mlx_pixel_put(data, coord[1], coord[0], col);
		}
	}
	free(matrix);
	return (0);
}
