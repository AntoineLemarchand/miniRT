/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:36:23 by egeorgio          #+#    #+#             */
/*   Updated: 2022/07/13 16:36:25 by egeorgio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	vec_rotationx(int keycode, t_data *data)
{
	double	tmp;

	tmp = data->scene->cam->orientation.z;
	if (keycode == KEYD)
	{
		data->scene->cam->orientation.z = cos(0.1)
			* data->scene->cam->orientation.z + sin(0.1)
			* data->scene->cam->orientation.y;
		data->scene->cam->orientation.y = cos(0.1)
			* data->scene->cam->orientation.y - sin(0.1) * tmp;
	}
	else if (keycode == KEYU)
	{
		data->scene->cam->orientation.z = cos(0.1)
			* data->scene->cam->orientation.z - sin(0.1)
			* data->scene->cam->orientation.y;
		data->scene->cam->orientation.y = cos(0.1)
			* data->scene->cam->orientation.y + sin(0.1) * tmp;
	}
}

void	vec_rotationy(int keycode, t_data *data)
{
	double	tmp;

	tmp = data->scene->cam->orientation.z;
	if (keycode == KEYR)
	{
		data->scene->cam->orientation.z = cos(0.1)
			* data->scene->cam->orientation.z + sin(0.1)
			* data->scene->cam->orientation.y;
		data->scene->cam->orientation.x = cos(0.1)
			* data->scene->cam->orientation.x + sin(0.1) * tmp;
	}
	else if (keycode == KEYL)
	{
		data->scene->cam->orientation.z = sin(0.1)
			* data->scene->cam->orientation.x + cos(0.1)
			* data->scene->cam->orientation.z;
		data->scene->cam->orientation.x = cos(0.1)
			* data->scene->cam->orientation.x - sin(0.1) * tmp;
	}
}

void	vec_translate(int keycode, t_data *data, t_vec **matrix)
{
	*matrix = compute_cam(data->scene->cam);
	vec_multiply(&matrix[0][0], 4);
	vec_multiply(&matrix[0][1], 4);
	vec_multiply(&matrix[0][2], 4);
	if (keycode == KEY8)
		vec_add(&data->scene->cam->position,
			&matrix[0][2], &data->scene->cam->position);
	else if (keycode == KEY2)
		vec_reduce(&data->scene->cam->position,
			&matrix[0][2], &data->scene->cam->position);
	else if (keycode == KEY4)
		vec_reduce(&data->scene->cam->position,
			&matrix[0][0], &data->scene->cam->position);
	else if (keycode == KEY6)
		vec_add(&data->scene->cam->position,
			&matrix[0][0], &data->scene->cam->position);
	else if (keycode == KEYP)
		vec_reduce(&data->scene->cam->position,
			&matrix[0][1], &data->scene->cam->position);
	else if (keycode == KEYM)
		vec_add(&data->scene->cam->position,
			&matrix[0][1], &data->scene->cam->position);
}

int	manage_key(int keycode, t_data *data)
{
	t_vec	*matrix;

	end_mlx(keycode, data);
	vec_translate(keycode, data, &matrix);
	vec_rotationx(keycode, data);
	vec_rotationy(keycode, data);
	free(matrix);
	compute_rays(data->scene, data, NULL, NULL);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
