/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 22:47:07 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/31 13:33:44 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	arrlen(char **arr)
{
	int	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

int	is_all_blank(char *line)
{
	int	is_all_blank;
	int	i;

	is_all_blank = 1;
	i = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r')))
			is_all_blank = 0;
		i++;
	}
	return (is_all_blank);
}

char	*get_next_word(char *line, int pass_word)
{
	int	i;

	i = 0;
	if (pass_word)
		while (line[i] && !(line[i] == ' ' || (line[i] <= '\r'
					&& line[i] >= '\t')))
			i++;
	while (line[i] && (line[i] == ' ' || (line[i] <= '\r' && line[i] >= '\t')))
		i++;
	return (line + i);
}

int	word_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !(line[i] == ' ' || (line[i] <= '\r' && line[i] >= '\t')))
		i++;
	return (i);
}

double	ft_atof(const char *s)
{
	double	val;
	int		comma;
	int		sign;

	val = 0.;
	comma = 0;
	sign = 1;
	if (*s == '-' && ++s)
		sign = -1;
	while (*s && ft_isdigit(*s))
		val = val * 10. + (*s++ - '0');
	if (*s++ == '.')
	{
		while (*s && ft_isdigit(*s))
		{
			val = val * 10. + (*s++ - '0');
			comma++;
		}
	}
	while (comma--)
		val *= .10;
	return (val * sign);
}
