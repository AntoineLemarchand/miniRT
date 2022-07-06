/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:40:17 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/06 11:40:44 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	*fail_helper(t_objs *objs)
{
	if (objs)
		free_objs(&objs);
	return (NULL);
}

char	*load_light(t_light **light, char *line)
{
	(*light)->position = get_vec_range(line);
	line = get_next_word(line, 1);
	(*light)->ratio = ft_atof(line);
	line = get_next_word(line, 1);
	(*light)->col = get_col_range(line);
	return (line);
}
