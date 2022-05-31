/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:37:36 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/31 14:06:27 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_objs	*obj_add_back(t_objs *list, t_objs *new)
{
	t_objs	*current;

	if (!list)
		return (new);
	current = list;
	while (current->next)
		current = current->next;
	current->next = new;
	return (list);
}

void	add_spheres_back(t_objs *ret, char **content, char *line, t_objs *new)
{
	while (*content)
	{
		line = get_next_word(*content, 0);
		if (!ft_strncmp(line, "sp", 2))
		{
			new = malloc(sizeof(t_sphere));
			if (!new)
			{
				free_objs(&ret);
				ret = NULL;
				return ;
			}
			new->next = NULL;
			new->type = sphere;
			new->val = (void *)new_sphere(get_next_word(line, 1));
			if (!new->val)
			{
				free_objs(&ret);
				ret = NULL;
				return ;
			}
			obj_add_back(ret, new);
		}
		content++;
	}
}

void	add_planes_back(t_objs *ret, char **content, char *line, t_objs *new)
{
	while (*content)
	{
		line = get_next_word(*content, 0);
		if (!ft_strncmp(line, "pl", 2))
		{
			new = malloc(sizeof(t_sphere));
			if (!new)
			{
				free_objs(&ret);
				ret = NULL;
				return ;
			}
			new->next = NULL;
			new->type = plane;
			new->val = (void *)new_plane(get_next_word(line, 1));
			if (!new->val)
			{
				free_objs(&ret);
				ret = NULL;
				return ;
			}
			obj_add_back(ret, new);
		}
		content++;
	}
}

void	add_cylinders_back(t_objs *ret, char **content, char *line, t_objs *new)
{
	while (*content)
	{
		line = get_next_word(*content, 0);
		if (!ft_strncmp(line, "cy", 2))
		{
			new = malloc(sizeof(t_sphere));
			if (!new)
			{
				free_objs(&ret);
				ret = NULL;
				return ;
			}
			new->next = NULL;
			new->type = cylinder;
			new->val = (void *)new_cylinder(get_next_word(line, 1));
			if (!new->val)
			{
				free_objs(&ret);
				ret = NULL;
				return ;
			}
			obj_add_back(ret, new);
		}
		content++;
	}
}
