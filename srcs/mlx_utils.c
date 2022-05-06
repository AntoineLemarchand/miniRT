/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:25:36 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/06 13:38:00 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	end_mlx(int keycode, t_data *data)
{
	(void)keycode;
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

int	end_virtual_mlx(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	ft_initdata(t_data *data, char *name)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, RES_X, RES_Y, name);
	data->img = mlx_new_image(data->mlx, RES_X, RES_Y);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

static void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_fill_screen(t_data *data, int (*f)(int, int, int))
{
	float		i;
	float		j;

	i = 0;
	j = 0;
	while (i < RES_X)
	{
		j = 0;
		while (j < RES_Y)
		{
			ft_mlx_pixel_put(data, i, j, f(i, j, i + j));
			j++;
		}
		i++;
	}
	return (0);
}
