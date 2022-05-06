/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:43:37 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/06 13:37:21 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	testcol(int R, int G, int B)
{
	return (R << 24 | G << 16 | B << 8);
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
	ft_fill_screen(&img, testcol);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_hook(img.win, 2, 1L << 0, end_mlx, &img);
	mlx_hook(img.win, 33, 1L << 17, end_virtual_mlx, &img);
	mlx_loop(img.mlx);
}
