/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:37:24 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/12 13:39:53 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_scene	*init_lights(char **content)
{
	(void)content;
	return (NULL);
}

static t_scene	*init_shapes(char **content)
{
	(void)content;
	return (NULL);
}

static t_scene	*init_cam(char **content)
{
	(void)content;
	return (NULL);
}

t_scene	*init_scene(char *file)
{
	char		**content;
	t_scene		*scene;

	content = check_file(file);
	if (content == NULL)
		return (NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->ambient = NULL;
	scene->light = NULL;
	scene->shapes = NULL;
	scene->cam = NULL;
	scene = init_lights(content);
	scene = init_shapes(content);
	scene = init_cam(content);
	if (!scene || !scene->cam || !scene->light
		|| !scene->ambient || !scene->shapes)
	{
		free_scene(scene);
		scene = NULL;
	}
	return (scene);
}
