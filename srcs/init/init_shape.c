/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:54:24 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/27 13:56:35 by alemarch         ###   ########.fr       */
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
	line = get_next_word(line, 1);
	ret->diameter = ft_atof(line);
	line = get_next_word(line, 1);
	ret->height = ft_atof(line);
	line = get_next_word(line, 1);
	ret->col = get_col_range(line);
	if (!ret->col)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
