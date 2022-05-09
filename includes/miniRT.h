/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 23:34:36 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/09 16:26:57 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include "mlx.h"

# define RES_X 800
# define RES_Y 800

# define ESC 65307

enum	type { AMBIENT, LIGHT, SPHERE, PLANE, CYLINDER }

// vect
typedef struct s_vec {
	float	x;
	float	y;
	float	z;
}	t_vec;

// https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
// figure 23
typedef	struct s_ray {
	t_vec	position;
	t_vec	offset;
}

// mlx struct
typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

// obj_utils.c
void	ft_puterror(char *err);

// mlx_utils.c
int		ft_fill_screen(t_data *data, int (*f)(int, int, int));
int		end_mlx(int keycode, t_data *data);
int		end_virtual_mlx(t_data *data);
void	ft_initdata(t_data *data, char *name);

#endif
