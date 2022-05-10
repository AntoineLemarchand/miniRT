/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 23:34:36 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/10 09:55:32 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

# define RES_X 800
# define RES_Y 800

# define ESC 65307

// vect
typedef struct s_vec {
	float	x;
	float	y;
	float	z;
}	t_vec;

// https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
// figure 23
// equation: P(t) = position + t * offset, t >= 0
// cf fig 24
typedef struct s_ray {
	t_vec	position;
	t_vec	offset;
}	t_ray;

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

// primary objs
typedef struct s_camera {
	t_vec	position;
	t_vec	orientation;
	int		fov;
}	t_camera;

typedef struct s_ambient {
	float	ratio;
	int		col;
}	t_ambient;

typedef struct s_light {
	float	ratio;
	t_vec	position;
	int		col;
}	t_light;

// shapes objs
// sphere equation: powf(x, 2.) + powf(y, 2.) + powf(z, 2.) = diameter / 2
typedef struct s_sphere {
	t_vec	position;
	float	diameter;
	int		col;
}	t_sphere;

typedef struct s_plane {
	t_vec	position;
	t_vec	orientation;
	int		col;
}	t_plane;

typedef struct s_cylinder {
	t_vec	position;
	t_vec	orientation;
	float	diameter;
	float	height;
	int		col;
}	t_cylinder;

// obj_utils.c
void	ft_puterror(char *err);

// mlx_utils.c
int		ft_fill_screen(t_data *data, int (*f)(int, int, int));
int		end_mlx(int keycode, t_data *data);
int		end_virtual_mlx(t_data *data);
void	ft_initdata(t_data *data, char *name);

#endif
