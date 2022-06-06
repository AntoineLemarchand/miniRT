/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:13:09 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/06 16:06:33 by alemarch         ###   ########.fr       */
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

// this is going to need a bit more work using light attenuation
// https://www.cs.utexas.edu/~theshark/courses/cs354/lectures/cs354-4.pdf
// slide 53
int	compute_primary_ray(t_ray *ray, t_scene *scene)
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
	return (get_shaded_col(ret, ray, scene));
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
