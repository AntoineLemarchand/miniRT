/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 23:34:36 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/12 11:53:08 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

# define RES_X 800
# define RES_Y 800

# define ESC 65307

// most math comes from:
// https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html

// vect
typedef struct s_vec {
	float	x;
	float	y;
	float	z;
}	t_vec;

// equation: P(t) = position + t * offset, t >= 0
// cf fig 23 and 24
typedef struct s_ray {
	t_vec	origin;
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

// plane equation: point Q is on plane if orientation * (position - Q) == 0
// figure 59
typedef struct s_plane {
	t_vec	position;
	t_vec	orientation;
	int		col;
}	t_plane;

//https://math.stackexchange.com/
//questions/875569/simple-geometry-question-equation-of-cylinder
// cylinder equation ():
// powf((position.y - position.z), 2.) + powf((position.z - position.x), 2.)
// + powf((position.x - position.y), 2.) == pwf(3 * orientation, 2.)
typedef struct s_cylinder {
	t_vec	position;
	t_vec	orientation;
	float	diameter;
	float	height;
	int		col;
}	t_cylinder;

// scene obj

enum	shape_type { NONE, SPHERE, PLANE, CYLINDER };
enum	scene_type { AMBIENT, LIGHT };

typedef struct s_objs {
	int				type;
	void			*val;
	struct s_objs	*next;
}	t_objs;

typedef struct s_scene {
	t_camera	*cam;
	t_ambient	*ambient;
	t_light		*light;
	t_objs		*shapes;
}	t_scene;

// get_next_line.c
char	*get_next_line(int fd);

// obj_utils.c
void	ft_puterror(char *err);

// mlx_utils.c
int		ft_fill_screen(t_data *data, int *rays);
int		end_mlx(int keycode, t_data *data);
int		end_virtual_mlx(t_data *data);
void	ft_initdata(t_data *data, char *name);

// init_utils.c
void	free_array(char **arr);
int		arrlen(char **arr);

// vec_basic.c
t_vec	*new_vec(float x, float y, float z);
void	vec_multiply(t_vec *vec, float f);
void	vec_divide(t_vec *vec, float f);

// vec_alg.c
void	vec_normalize(t_vec *vec);
float	vec_dot_product(t_vec *v1, t_vec *v2);
t_vec	*vec_cross_product(t_vec *v1, t_vec *v2);

// free_utils.c
void	free_objs(t_objs *objs);
void	free_scene(t_scene *scene);
void	free_array(char **arr);

// init_file.c
char	**check_file(char *file);

// init_scene.c
t_scene	*init_scene(char *file);

#endif
