/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:24:35 by alemarch          #+#    #+#             */
/*   Updated: 2022/06/02 11:48:45 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_puterror(char *err)
{
	write(2, "Error\nminiRT: ", 6);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
}

char	*get_content_line(char **content, const char *toFind)
{
	while (*content)
	{
		if (!ft_strncmp(*content, toFind, ft_strlen(toFind)))
			return (*content);
		content++;
	}
	return (NULL);
}

int	get_col(int R, int G, int B)
{
	return (R << 16 | G << 8 | B);
}

t_vec	get_vec_range(char *content)
{
	t_vec	ret;

	ret.x = ft_atof(content);
	while (*content != ',')
		content++;
	content++;
	ret.y = ft_atof(content);
	while (*content != ',')
		content++;
	content++;
	ret.z = ft_atof(content);
	return (ret);
}

int	*get_col_range(char *content)
{
	int	*ret;

	ret = malloc(sizeof(int) * 3);
	if (!ret)
		return (NULL);
	ret[0] = ft_atoi(content);
	while (*content && *content != ',')
		content++;
	if (*content)
		content++;
	ret[1] = ft_atoi(content);
	while (*content && *content != ',')
		content++;
	if (*content)
		content++;
	ret[2] = ft_atoi(content);
	return (ret);
}
