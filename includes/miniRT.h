/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 23:34:36 by alemarch          #+#    #+#             */
/*   Updated: 2022/05/13 18:46:19 by alemarch         ###   ########.fr       */
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
	int		*col;
}	t_ambient;

typedef struct s_light {
	float	ratio;
	t_vec	position;
	int		*col;
}	t_light;

// shapes objs
// sphere equation: powf(x, 2.) + powf(y, 2.) + powf(z, 2.) = diameter / 2
typedef struct s_sphere {
	t_vec	position;
	float	diameter;
	int		*col;
}	t_sphere;

// plane equation: point Q is on plane if orientation * (position - Q) == 0
// figure 59
typedef struct s_plane {
	t_vec	position;
	t_vec	orientation;
	int		*col;
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
	int		*col;
}	t_cylinder;

// scene obj

enum	scene_type { NONE, SPHERE, PLANE, CYLINDER, AMBIENT, LIGHT };

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
char	*get_content_line(char **content, const char *toFind);
int		get_col(int R, int G, int B);
t_vec	get_vec_range(char *content);
int	*get_col_range(char *content);

// mlx_utils.c
int		ft_fill_screen(t_data *data, int *rays);
int		end_mlx(int keycode, t_data *data);
int		end_virtual_mlx(t_data *data);
void	ft_initdata(t_data *data, char *name);

// init_utils.c
int		arrlen(char **arr);
int		is_all_blank(char *line);
char	*get_next_word(char *line, int pass_word);
int		word_len(char *line);
double	ft_atof(const char *s);

// vec_basic.c
t_vec	*new_vec(float x, float y, float z);
void	vec_multiply(t_vec *vec, float f);
void	vec_divide(t_vec *vec, float f);

// vec_alg.c
void	vec_normalize(t_vec *vec);
float	vec_dot_product(t_vec *v1, t_vec *v2);
t_vec	*vec_cross_product(t_vec *v1, t_vec *v2);

// free_utils.c
void	free_objs(t_objs **objs);
void	free_scene(t_scene *scene);
void	free_array(char **arr);

// check_objs.c
int	check_camera_line(char *line);
int	check_ambient_line(char *line);
int	check_light_line(char *line);

// check_shape.c
int	check_sphere_line(char *line);
int	check_plane_line(char *line);
int	check_cylinder_line(char *line);

// init_file.c
char	**check_file(char *file);

// init_shape.c
t_sphere	*new_sphere(char *line);
t_plane		*new_plane(char *line);
t_cylinder	*new_cylinder(char *line);

// init_shapes.c
void	add_spheres_back(t_objs *ret, char **content, char *line, t_objs *new);
void	add_planes_back(t_objs *ret, char **content, char *line, t_objs *new);
void	add_cylinders_back(t_objs *ret, char **content, char *line,
	t_objs *new);

// init_scene.c
t_scene	*init_scene(char *file);

#endif
