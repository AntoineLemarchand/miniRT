/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:43:37 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/12 11:11:58 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_col(int R, int G, int B)
{
	return (R << 24 | G << 16 | B << 8);
}

int	*compute_scene(t_scene *scene)
{
	(void)scene;
	return (NULL);
}

int	quit( t_data *data )
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(1);
}

int	main(int ac, char **av)
{
	//t_data	img;
	t_scene	*scene;
	//int		*cols;

	if (ac != 2)
	{
		ft_puterror("Please enter the name of a .rt file only");
		return (1);
	}
	//ft_initdata(&img, av[1]);
	scene = init_scene(av[1]);
	if (!scene)
		ft_puterror("Corrupted file");
	/*
	if (!scene)
		quit(&img);
	cols = compute_scene(scene);
	if (!cols)
		ft_puterror("Raycast failed");
	if (!cols)
		quit(&img);
	ft_fill_screen(&img, NULL);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_hook(img.win, 2, 1L << 0, end_mlx, &img);
	mlx_hook(img.win, 33, 1L << 17, end_virtual_mlx, &img);
	mlx_loop(img.mlx);
	*/
}
