/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:23:13 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/06 12:35:08 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	add_vecs(t_vec v1, t_vec v2)
{
	t_vec	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

void	init_triangle(t_ray *ray, t_triangle *triangle, t_vec *side, t_vec *p)
{
	double	t;
	t_vec	m;

	m = ray->offset;
	new_vec(triangle->pb.x - triangle->pa.x, triangle->pb.y - triangle->pa.y,
		triangle->pb.z - triangle->pa.z, &side[0]);
	new_vec(triangle->pc.x - triangle->pb.x, triangle->pc.y - triangle->pb.y,
		triangle->pc.z - triangle->pb.z, &side[1]);
	new_vec(triangle->pa.x - triangle->pc.x, triangle->pa.y - triangle->pc.y,
		triangle->pa.z - triangle->pc.z, &side[2]);
	p->x = triangle->pa.x - ray->origin.x;
	p->y = triangle->pa.y - ray->origin.y;
	p->z = triangle->pa.z - ray->origin.z;
	t = vec_dot_product(&triangle->orientation, p)
		/ vec_dot_product(&triangle->orientation, &ray->offset);
	vec_multiply(&m, t);
	m = add_vecs(m, ray->origin);
	new_vec(m.x - triangle->pa.x, m.y - triangle->pa.y,
		m.z - triangle->pa.z, &side[3]);
	new_vec(m.x - triangle->pb.x, m.y - triangle->pb.y,
		m.z - triangle->pb.z, &side[4]);
	new_vec(m.x - triangle->pc.x, m.y - triangle->pc.y,
		m.z - triangle->pc.z, &side[5]);
}

// side[0] : AB, side[1] : BC, side[2] : CA, side[3] : AM, side[4] : BM,
//  side[5] : CM side[6] : BA side[7] : CB side[8] : AC

double	get_triangle_dist(t_ray *ray, t_triangle *triangle)
{
	double	ret;
	t_vec	side[9];
	t_vec	point;
	t_vec	crossp[6];

	init_triangle(ray, triangle, side, &point);
	side[6] = vec_inv(side[0]);
	side[7] = vec_inv(side[1]);
	side[8] = vec_inv(side[2]);
	if (fabs(vec_dot_product(&triangle->orientation, &ray->offset)) > 0.00001)
		ret = vec_dot_product(&triangle->orientation, &point)
			/ vec_dot_product(&triangle->orientation, &ray->offset);
	else
		return (-1);
	vec_cross_product(&side[0], &side[3], &crossp[0]);
	vec_cross_product(&side[3], &side[8], &crossp[1]);
	vec_cross_product(&side[6], &side[4], &crossp[2]);
	vec_cross_product(&side[4], &side[1], &crossp[3]);
	vec_cross_product(&side[2], &side[5], &crossp[4]);
	vec_cross_product(&side[5], &side[7], &crossp[5]);
	if (vec_dot_product(&crossp[0], &crossp[1]) < 0
		|| vec_dot_product(&crossp[2], &crossp[3]) < 0
		|| vec_dot_product(&crossp[4], &crossp[5]) < 0)
		ret = -1;
	return (ret);
}
