/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:11:23 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/22 16:11:35 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*next_float(char *line)
{
	if (*line == '-')
		line++;
	while (*line && ft_isdigit(*line))
		line++;
	if (*line == '.')
		line++;
	while (*line && ft_isdigit(*line))
		line++;
	return (line);
}

int	check_float_trio(char *line)
{
	if (line == next_float(line))
		return (1);
	line = next_float(line);
	if (*line != ',')
		return (1);
	line++;
	if (line == next_float(line))
		return (1);
	line = next_float(line);
	if (*line != ',')
		return (1);
	line++;
	if (line == next_float(line))
		return (1);
	line = next_float(line);
	if ((*line > '\t' && *line < '\r') || *line == ' ')
		return (0);
	return (1);
}

int	check_uint8_trio(char *line)
{
	if (ft_atoi(line) < 0 || ft_atoi(line) > 255)
		return (1);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line != ',')
		return (1);
	line++;
	if (ft_atoi(line) < 0 || ft_atoi(line) > 255)
		return (1);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line != ',')
		return (1);
	line++;
	if (ft_atoi(line) < 0 || ft_atoi(line) > 255)
		return (1);
	while (*line && ft_isdigit(*line))
		line++;
	if ((*line > '\t' && *line < '\r') || *line == ' ')
		return (0);
	return (1);
}
