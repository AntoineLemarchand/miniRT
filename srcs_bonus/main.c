/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:43:37 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/06 12:07:32 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	img.scene = init_scene(av[1], NULL);
	if (!img.scene)
	{
		ft_puterror("Corrupted file");
		return (1);
	}
	ft_initdata(&img, av[1]);
	if (compute_rays(img.scene, &img, NULL, NULL))
	{
		ft_puterror("Raycast failed");
		quit(&img);
	}
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	printf("%s: %s rendered\n", av[0], av[1]);
	mlx_hook(img.win, 2, 1L << 0, manage_key, &img);
	mlx_hook(img.win, 33, 1L << 17, end_virtual_mlx, &img);
	mlx_loop(img.mlx);
}
