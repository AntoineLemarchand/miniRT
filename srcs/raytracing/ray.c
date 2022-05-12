/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:13:09 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/11 14:14:39 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	arrlen(int	*rays)
{
	int	size;

	size = 0;
	while (rays[size])
		size++;
	return (size);
}

t_ray	*new_ray(t_vec *position, t_vec *offset)
{
	t_ray	*ret;

	if (!position || !offset)
		return (NULL);
	ret = malloc(sizeof(t_ray));
	if (!ret)
		return (NULL);
	ret.position.x = position->x;
	ret.position.y = position->y;
	ret.position.z = position->z;
	ret.offset.x = offset->x;
	ret.offset.y = offset->y;
	ret.offset.z = offset->z;
	return (ret);
}

static int	*add_computed_ray(int *arr, int computed_ray)
{
	int		size;
	int		i;
	t_ray	*ret;

	if (!arr)
		return (NULL);
	size = arrlen(rays);
	ret = ft_calloc((size + 2) * sizeof(t_ray));
	if (!ret)
	{
		free(computed_ray);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		ret[i] = rays[i];
		i++;
	}
	ret[i] = computed_ray;
	return (ret);
}

// this is going to need a bit more work using light attenuation
// https://www.cs.utexas.edu/~theshark/courses/cs354/lectures/cs354-4.pdf
// diapo 53
/*
two arguments are needed shapes and lights
89 while has not hit any shape or light
return value: 0 if shape or attenuated ratio if light
*/
int	compute_shadow_ray(t_vec *point, t_vec	*position)
{
	int		t;
	t_ray	ray;
	t_vec	ray_point;

	ray.origin = *point;
	ray.offset = *position;
	vec_normalize(ray.offset);
	ray_point.x = ray.origin.x;
	ray_point.y = ray.origin.y;
	ray_point.z = ray.origin.z;
	t = 1;
	while (1 < 100)
	{
		ray_point.x = ray.origin.x + t * ray.offset.x ;
		ray_point.y = ray.origin.y + t * ray.offset.x ;
		ray_point.z = ray.origin.z + t * ray.offset.x ;
		t++;
	}
	return (1);
}

/*
two arguments are needed shapes and lights
119 while has not hit any shape or light
127 for each light and ambient objects shoot a shadow ray (lights[i])
ratio += computeshadowray(&ray_point, light[i].position)
return value: getcol(getR(shape.col), getR(shape.col), getR(shape.col)) * ratio
*/
int	compute_primary_ray(t_vec *origin, t_vec *offset)
{
	int		t;
	float	ratio;
	t_ray	ray;
	t_vec	ray_point;

	ray.origin = *origin;
	ray.offset = *offset;
	ray_point.x = ray.origin.x;
	ray_point.y = ray.origin.y;
	ray_point.z = ray.origin.z;
	t = 1;
	while (1 < 100)
	{
		ray_point.x = ray.origin.x + t * ray.offset.x ;
		ray_point.y = ray.origin.y + t * ray.offset.x ;
		ray_point.z = ray.origin.z + t * ray.offset.x ;
		t++;
	}
	return (0x00FF0000);
}

/*
147 - 149: origin.x = camera.position.x
      153: offset.x = camera.fov
*/
int	*compute_rays(t_camera cam)
{
	int		y;
	int		x;
	int		*computed_rays;
	t_vec	origin;
	t_vec	offset;


	rays = NULL;
	y = 0;
	while (y < RES_X)
	{
		x = 0;
		while(x < RES_Y)
		{
			origin.x = origin.y = origin.z = 0;
			offset.x = x;
			offset.x = y;
			offset.z = 80;
			vec_normalize(offset);
			computed_ray = add_computed_ray(computed_ray,
					compute_primary_ray(origin, offset));
			if (!computed_ray)
				return (NULL);
		}
	}
	return(computed_ray);
}

