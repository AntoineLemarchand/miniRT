/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:12:07 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/27 12:58:45 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_camera_line(char *line)
{
	if (check_float_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (check_float_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (!line)
		return (1);
	if (ft_atoi(line) < 0 || ft_atoi(line) > 180)
		return (1);
	while (*line && ft_isdigit(*line))
		line++;
	line = get_next_word(line, 0);
	if (*line)
		return (1);
	return (0);
}

int	check_ambient_line(char *line)
{
	if (ft_atof(line) < 0. || ft_atof(line) > 1.)
		return (1);
	line = get_next_word(line, 1);
	if (!line)
		return (1);
	if (check_uint8_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (*line)
		return (1);
	return (0);
}

int	check_light_line(char *line)
{
	if (check_float_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (!line || ft_atof(line) < 0. || ft_atof(line) > 1.)
		return (1);
	line = get_next_word(line, 1);
	if (!line || check_uint8_trio(line))
		return (1);
	line = get_next_word(line, 1);
	if (*line)
		return (1);
	return (0);
}
