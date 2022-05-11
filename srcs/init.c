/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:37:24 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/11 21:51:30 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	**check_file(char *file)
{
	int		fd;
	char	**ret;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	ret = NULL
	return (ret);
}

t_objs	*init_lights(char *content)
{
	(void)content;
	return (NULL);
}

t_objs	*init_shapes(char *content)
{
	(void)content;
	return (NULL);
}

t_camera	*init_cam(char *content)
{
	(void)content;
	return (NULL);
}

t_scene	*init_scene(char *file)
{
	char		*content;
	t_scene		*ret;

	content = check_file(file);
	if (content == NULL)
		return (NULL);
	ret = malloc(sizeof(t_scene));
	if (!ret)
		return (NULL);
	ret->lights = NULL;
	ret->shapes = NULL;
	ret->cam = NULL;
	ret->lights = init_lights(content);
	ret->shapes = init_shapes(content);
	ret->cam = init_cam(content);
	if (!ret->cam || !ret->lights || !ret->shapes)
	{
		free_scene(ret);
		ret = NULL;
	}
	return (ret);
}

