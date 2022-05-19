/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:43:37 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/19 09:50:33 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	*compute_scene(t_scene *scene)
{
	int *ret;
	
	ret = compute_rays(scene);
	return (ret);
}

int	quit( t_data *data)
{
	if (data)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		if (data->scene)
			free_scene(data->scene);
	}
	exit(1);
}

int	main(int ac, char **av)
{
	t_data	img;

	if (ac != 2)
	{
		ft_puterror("Please enter the name of a .rt file only");
		return (1);
	}
	ft_initdata(&img, av[1]);
	img.scene = init_scene(av[1]);
	if (!img.scene)
	{
		ft_puterror("Corrupted file");
		quit(&img);
	}
	img.cols = compute_scene(img.scene);
	if (!img.cols)
	{
		ft_puterror("Raycast failed");
		quit(&img);
	}
	ft_fill_screen(&img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_hook(img.win, 2, 1L << 0, end_mlx, &img);
	mlx_hook(img.win, 33, 1L << 17, end_virtual_mlx, &img);
	mlx_loop(img.mlx);
}
