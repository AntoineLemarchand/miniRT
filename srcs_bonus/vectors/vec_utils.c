/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:53:13 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/12 15:04:32 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	vec_same_dir(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z > 0);
}

double	vec_len(t_vec *vec)
{
	return (sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}
