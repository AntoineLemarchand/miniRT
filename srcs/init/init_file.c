/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:37:24 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/11 22:52:45 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	check_line(char *line)
{
	(void)line;
	return (0);
}

static int	add_line(char ***arr, char *line)
{
	int		size;
	char	**ret;
	
	if (!*arr)
		size = 0;
	else
		size = arrlen(*arr);
	ret = ft_calloc(sizeof(arr), size + 2);
	if (!ret)
		return (1);
	while (size)
	{
		size--;
		ret[size] = *arr[size];
	}
	ret[arrlen(*arr)] = line;
	if (*arr)
		free(*arr);
	*arr = ret;
	return (0);
}

char	**check_file(char *file)
{
	int		fd;
	char	**ret;
	char	*line;

	fd = open(file, O_RDONLY);
	ret = NULL;
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (check_line(line), add_line(&ret, line))
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
