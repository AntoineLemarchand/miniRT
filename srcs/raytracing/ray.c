/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:13:09 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/19 09:57:00 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// this is going to need a bit more work using light attenuation
// https://www.cs.utexas.edu/~theshark/courses/cs354/lectures/cs354-4.pdf
// diapo 53
/*
two arguments are needed shapes and lights
89 while has not hit any shape or light
return value: 0 if shape or attenuated ratio if light
int	compute_shadow_ray(t_vec *point, t_vec	*position)
{
	int		t;
	t_ray	ray;
	t_vec	ray_point;

	ray.origin = *point;
	ray.offset = *position;
	vec_normalize(&ray.offset);
	ray_point.x = ray.origin.x;
	ray_point.y = ray.origin.y;
	ray_point.z = ray.origin.z;
	t = 1;
	while (t < MAX_DIST)
	{
		ray_point.x = ray.origin.x + t * ray.offset.x ;
		ray_point.y = ray.origin.y + t * ray.offset.x ;
		ray_point.z = ray.origin.z + t * ray.offset.x ;
		t++;
	}
	return (1);
}
*/

/*
two arguments are needed shapes and lights
119 while has not hit any shape or light
127 for each light and ambient objects shoot a shadow ray (lights[i])
ratio += computeshadowray(&ray_point, light[i].position)
return value: getcol(getR(shape.col), getR(shape.col), getR(shape.col)) * ratio
*/
int	compute_primary_ray(t_ray *ray, t_scene *scene)
{
	int		t;
	//float	ratio;
	t_vec	primary_ray;

	t = 1;
	(void)primary_ray;
	(void)scene;
	while (/*!shape_hit(ray_point, scene) &&*/ t > MAX_DIST)
	{
		primary_ray.x = ray->origin.x + t * ray->offset.x ;
		primary_ray.y = ray->origin.y + t * ray->offset.x ;
		primary_ray.z = ray->origin.z + t * ray->offset.x ;
		t++;
	}
	return (0x00FF0000);
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
	ret->offset.x = x;
	ret->offset.y = y;
	ret->offset.z = camera->fov;
	vec_normalize(&ret->offset);
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
	while (y < RES_X)
	{
		x = 0;
		while(x < RES_Y)
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
