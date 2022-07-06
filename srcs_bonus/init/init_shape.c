/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:54:24 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/06 13:24:04 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_sphere	*new_sphere(char *line)
{
	t_sphere	*ret;

	ret = malloc(sizeof(t_sphere));
	if (!ret)
		return (NULL);
	ret->position = get_vec_range(line);
	line = get_next_word(line, 1);
	ret->diameter = ft_atof(line);
	line = get_next_word(line, 1);
	ret->col = get_col_range(line);
	if (!ret->col)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

t_plane	*new_plane(char *line)
{
	t_plane	*ret;

	ret = malloc(sizeof(t_plane));
	if (!ret)
		return (NULL);
	ret->position = get_vec_range(line);
	line = get_next_word(line, 1);
	ret->orientation = get_vec_range(line);
	if (ret->orientation.x == 0 && ret->orientation.y == 0
		&& ret->orientation.z == 0)
	{
		free(ret);
		return (NULL);
	}
	line = get_next_word(line, 1);
	ret->col = get_col_range(line);
	if (!ret->col)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

t_cylinder	*new_cylinder(char *line)
{
	t_cylinder	*ret;

	ret = malloc(sizeof(t_cylinder));
	if (!ret)
		return (NULL);
	ret->position = get_vec_range(line);
	line = get_next_word(line, 1);
	ret->orientation = get_vec_range(line);
	if (ret->orientation.x == 0 && ret->orientation.y == 0
		&& ret->orientation.z == 0)
	{
		free(ret);
		return (NULL);
	}
	line = get_next_word(line, 1);
	ret->diameter = ft_atof(line);
	line = get_next_word(line, 1);
	ret->height = ft_atof(line);
	line = get_next_word(line, 1);
	ret->col = get_col_range(line);
	if (!ret->col)
		free(ret);
	if (!ret->col)
		return (NULL);
	return (ret);
}

static int	get_triangle_orientation(t_triangle *ret)
{
	if (vec_equal(&ret->pa, &ret->pb) || vec_equal(&ret->pa, &ret->pc)
		|| vec_equal(&ret->pb, &ret->pc))
		return (1);
	ret->orientation.x = 0;
	ret->orientation.y = 1;
	ret->orientation.z = 0;
	return (0);
}

t_triangle	*new_triangle(char *line)
{
	t_triangle	*ret;

	ret = malloc(sizeof(t_triangle));
	if (!ret)
		return (NULL);
	ret->pa = get_vec_range(line);
	line = get_next_word(line, 1);
	ret->pb = get_vec_range(line);
	line = get_next_word(line, 1);
	ret->pc = get_vec_range(line);
	line = get_next_word(line, 1);
	ret->col = get_col_range(line);
	if (!ret->col || get_triangle_orientation(ret))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
