/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:37:24 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/12 13:39:28 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_all_blank(char *line)
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

static char	*get_next_word(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] <= '\r' || line[i] >= '\t'))
		i++;
	return (line + i);
}

static int	check_line(char *line)
{
	get_next_word(line);
	return (0);
}

static char	**add_line(char **arr, char *line)
{
	int		size;
	int		i;
	char	**ret;

	if (!arr)
		size = 0;
	else
		size = arrlen(arr);
	ret = ft_calloc(sizeof(char *), size + 2);
	i = 0;
	while (ret && i < size)
	{
		ret[i] = arr[i];
		i++;
	}
	if (arr)
		free(arr);
	if (ret)
		ret[size] = line;
	return (ret);
}

char	**check_file(char *file)
{
	int		fd;
	char	**ret;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	ret = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_all_blank(line))
			ret = add_line(ret, line);
		if (!ret || check_line(line))
		{
			if (ret)
				free_array(ret);
			free(line);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	return (ret);
}
