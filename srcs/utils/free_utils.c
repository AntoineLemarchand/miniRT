/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:35:36 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/11 22:56:35 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i]);
	free(arr);
}

void	free_objs(t_objs *objs)
{
	t_objs	*start;

	start = objs;
	if (objs)
	{
		while (objs)
		{
			free(objs->val);
			objs = objs->next;
		}
		free(start);
	}
}

void	free_scene(t_scene *scene)
{
	if (scene)
	{
		if (scene->lights)
			free_objs(scene->lights);
		if (scene->shapes)
			free_objs(scene->shapes);
		if (scene->cam)
			free(scene->cam);
		free(scene);
	}
}

