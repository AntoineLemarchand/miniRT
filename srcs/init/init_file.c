/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:37:24 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/22 16:09:29 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static int	check_line(char *line)
{
	int	len;

	if (is_all_blank(line))
		return (0);
	len = word_len(line);
	line = get_next_word(line, 0);
	if (*line == '#')
		return (0);
	if (len == 1 && *line == 'C')
		return (check_camera_line(get_next_word(line, 1)));
	else if (len == 1 && *line == 'A')
		return (check_ambient_line(get_next_word(line, 1)));
	else if (len == 1 && *line == 'L')
		return (check_light_line(get_next_word(line, 1)));
	else if (len == 2 && !ft_strncmp(line, "sp", 2))
		return (check_sphere_line(get_next_word(line, 1)));
	else if (len == 2 && !ft_strncmp(line, "pl", 2))
		return (check_plane_line(get_next_word(line, 1)));
	else if (len == 2 && !ft_strncmp(line, "cy", 2))
		return (check_cylinder_line(get_next_word(line, 1)));
	return (1);
}

void	flush_file(int fd, char *line)
{
	while (line)
	{
		line = get_next_line(fd);
		free(line);
	}
}

char	**check_file(char *file, char **ret)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!is_all_blank(line))
		{
			ret = add_line(ret, line);
			if (!ret || check_line(line))
			{
				if (ret)
					free_array(ret);
				flush_file(fd, line);
				return (NULL);
			}
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	return (ret);
}
