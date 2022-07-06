/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:07:27 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/06 12:19:35 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_sphere_line(char *line)
{
	if (check_float_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (line == next_float(line))
		return (1);
	line = next_float(line);
	line = get_next_word(line, 0);
	if (check_uint8_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (*line)
		return (1);
	return (0);
}

int	check_plane_line(char *line)
{
	if (check_float_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (check_float_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (check_uint8_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (*line)
		return (1);
	return (0);
}

int	check_cylinder_line(char *line)
{
	if (check_float_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (check_float_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (line == next_float(line))
		return (1);
	line = next_float(line);
	line = get_next_word(line, 1);
	if (line == next_float(line))
		return (1);
	line = next_float(line);
	line = get_next_word(line, 1);
	if (check_uint8_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (*line)
		return (1);
	return (0);
}
