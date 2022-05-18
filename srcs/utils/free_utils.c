/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:35:36 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/17 13:59:01 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static void	free_obj(t_objs *obj)
{
	if (obj->type == AMBIENT)
		free(((t_ambient *)(obj->val))->col);
	else if (obj->type == LIGHT)
		free(((t_light *)(obj->val))->col);
	else if (obj->type == SPHERE)
		free(((t_sphere *)(obj->val))->col);
	else if (obj->type == PLANE)
		free(((t_plane *)(obj->val))->col);
	else if (obj->type == CYLINDER)
		free(((t_cylinder *)(obj->val))->col);
	if (obj->val)
		free(obj->val);
	free(obj);
}

void	free_objs(t_objs **objs)
{
	t_objs	*curr;
	t_objs	*curr_next;

	curr = *objs;
	while (curr)
	{
		curr_next = curr->next;
		free_obj(curr);
		curr = curr_next;
	}
	*objs = NULL;
}

void	free_scene(t_scene *scene)
{
	if (scene)
	{
		if (scene->light)
		{
			free(scene->light->col);
			free(scene->light);
		}
		if (scene->ambient)
		{
			free(scene->ambient->col);
			free(scene->ambient);
		}
		if (scene->shapes)
			free_objs(&scene->shapes);
		if (scene->cam)
			free(scene->cam);
		free(scene);
	}
}
