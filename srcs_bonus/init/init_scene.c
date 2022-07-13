/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:37:24 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/13 15:45:41 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_camera	*init_cam(char **content)
{
	t_camera	*ret;
	char		*line;

	ret = malloc(sizeof(t_camera));
	if (!ret)
		return (NULL);
	line = get_next_word(get_content_line(content, "C"), 1);
	ret->position = get_vec_range(line);
	line = get_next_word(line, 1);
	ret->orientation = get_vec_range(line);
	if ((ret->orientation.x == 0 && ret->orientation.y == 0
			&& ret->orientation.z == 0) || fabs(ret->orientation.x) > 1
		|| fabs(ret->orientation.y) > 1 || fabs(ret->orientation.z) > 1)
	{
		free(ret);
		return (NULL);
	}
	line = get_next_word(line, 1);
	ret->fov = ft_atoi(line);
	return (ret);
}

static t_ambient	*init_ambient(char **content)
{
	t_ambient	*ret;
	char		*line;

	ret = malloc(sizeof(t_ambient));
	if (!ret)
		return (NULL);
	line = get_next_word(get_content_line(content, "A"), 1);
	ret->ratio = ft_atof(line);
	line = get_next_word(line, 1);
	ret->col = get_col_range(line);
	if (!ret->col)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

static t_objs	*init_lights(char **content, t_objs *curr, char *line)
{
	t_objs	*ret;

	ret = NULL;
	while (*content)
	{
		line = get_next_word(*content, 0);
		if (!ft_strncmp(line, "L", 1))
		{
			line = get_next_word(line, 1);
			curr = malloc(sizeof(t_objs));
			if (!curr)
				return (fail_helper(ret));
			curr->type = light;
			curr->val = malloc(sizeof(t_light));
			if (!curr->val)
				return (fail_helper(ret));
			line = load_light(((t_light **)&curr->val), line);
			if (!((t_light *)curr->val)->col)
				return (fail_helper(ret));
			curr->next = NULL;
			ret = obj_add_back(ret, curr);
		}
		content++;
	}
	return (ret);
}

static t_objs	*init_shapes(char **content)
{
	t_objs	*ret;

	ret = malloc(sizeof(t_objs));
	if (!ret)
		return (NULL);
	ret->type = none;
	ret->val = NULL;
	ret->next = NULL;
	add_spheres_back(&ret, content, NULL, NULL);
	if (!ret)
		return (NULL);
	add_planes_back(&ret, content, NULL, NULL);
	if (!ret)
		return (NULL);
	add_cylinders_back(&ret, content, NULL, NULL);
	if (!ret)
		return (NULL);
	add_triangles_back(&ret, content, NULL, NULL);
	if (!ret)
		return (NULL);
	return (ret);
}

t_scene	*init_scene(char *file, t_scene *scene)
{
	char		**content;

	content = check_file(file, NULL);
	if (content == NULL)
		return (NULL);
	if (check_double(content))
	{
		free_array(content);
		return (NULL);
	}
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->cam = init_cam(content);
	scene->ambient = init_ambient(content);
	scene->lights = init_lights(content, NULL, NULL);
	scene->shapes = init_shapes(content);
	free_array(content);
	if (!scene->cam || !scene->lights || !scene->ambient
		|| !scene->shapes)
	{
		free_scene(scene);
		scene = NULL;
	}
	return (scene);
}
