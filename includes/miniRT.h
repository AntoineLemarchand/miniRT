/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 23:34:36 by alemarch          #+#    #+#             */
/*   Updated: 2022/07/05 14:30:20 by alemarch         ###   ########.fr       */
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

# define RES_X 1000
# define RES_Y 1000

# define MAX_DIST 800

# define ESC 65307

// most math comes from:
// https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html

// vect
typedef struct s_vec {
	double	x;
	double	y;
	double	z;
}	t_vec;

// equation: P(t) = position + t * offset, t >= 0
// cf fig 23 and 24
typedef struct s_ray {
	t_vec	origin;
	t_vec	offset;
}	t_ray;

// to keep track of distances
typedef struct s_pixel {
	int		col;
	float	dist;
}	t_pixel;

// mlx struct
typedef struct s_data {
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	struct s_scene	*scene;
}	t_data;

// primary objs
typedef struct s_camera {
	t_vec	position;
	t_vec	orientation;
	int		fov;
}	t_camera;

typedef struct s_ambient {
	double	ratio;
	int		*col;
}	t_ambient;

typedef struct s_light {
	double	ratio;
	t_vec	position;
	int		*col;
}	t_light;

// shapes objs
// sphere equation: powf(x, 2.) + powf(y, 2.) + powf(z, 2.) = diameter / 2
typedef struct s_sphere {
	t_vec	position;
	double	diameter;
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
	double	diameter;
	double	height;
	int		*col;
}	t_cylinder;

// scene obj

enum	e_scene_type { none, sphere, plane, cylinder, ambient, light };

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
char		*get_next_line(int fd);

// obj_utils.c
void		ft_puterror(char *err);
char		*get_content_line(char **content, const char *toFind);
int			get_col(int R, int G, int B);
t_vec		get_vec_range(char *content);
int			*get_col_range(char *content);

// mlx_utils.c
int			end_mlx(int keycode, t_data *data);
int			end_virtual_mlx(t_data *data);
void		ft_initdata(t_data *data, char *name);
void		ft_mlx_pixel_put(t_data *data, int x, int y, int color);

// init_utils.c
int			arrlen(char **arr);
int			is_all_blank(char *line);
char		*get_next_word(char *line, int pass_word);
int			word_len(char *line);
double		ft_atof(const char *s);

// vec_basic.c
void		new_vec(double x, double y, double z, t_vec *ret);
void		vec_multiply(t_vec *vec, double f);
void		vec_divide(t_vec *vec, double f);
void		vec_reduce(t_vec *v1, t_vec *v2, t_vec *ret);
double		vec_len(t_vec *vec);

// vec_alg.c
void		vec_normalize(t_vec *vec);
double		vec_dot_product(t_vec *v1, t_vec *v2);
double		vec_distance(t_vec *v1, t_vec *v2);
void		vec_cross_product(t_vec *v1, t_vec *v2, t_vec *ret);

// free_utils.c
void		free_objs(t_objs **objs);
void		free_scene(t_scene *scene);
void		free_array(char **arr);

//	check_utils.c
char		*next_float(char *line);
int			check_float_trio(char *line);
int			check_uint8_trio(char *line);
int			check_double(char **content);

//	check_objs.c
int			check_camera_line(char *line);
int			check_ambient_line(char *line);
int			check_light_line(char *line);

// check_shape.c
int			check_sphere_line(char *line);
int			check_plane_line(char *line);
int			check_cylinder_line(char *line);

// init_file.c
char		**check_file(char *file, char **ret);

// init_shape.c
t_sphere	*new_sphere(char *line);
t_plane		*new_plane(char *line);
t_cylinder	*new_cylinder(char *line);

// init_shapes.c
void		add_spheres_back(t_objs **ret, char **content, char *line,
				t_objs *new);
void		add_planes_back(t_objs **ret, char **content, char *line,
				t_objs *new);
void		add_cylinders_back(t_objs **ret, char **content, char *line,
				t_objs *new);

// init_scene.c
t_scene		*init_scene(char *file, t_scene *scene);

// cam.c
t_vec		*compute_cam(t_camera *camera);
t_ray		*init_ray(t_camera *camera, t_vec *matrix, int x, int y);
t_vec		*build_ray_matrix(t_vec *offset, t_vec *matrix);

// trace_shapes.c
double		get_sphere_dist(t_ray *ray, t_sphere *sphere);
double		get_plane_dist(t_ray *ray, t_plane *plane);
double		get_cylinder_dist(t_ray *ray, t_cylinder *cylinder);

// shadow_ray.c
int			get_shaded_col(t_objs *obj, t_ray *ray, t_scene *scene);

// primary_ray.c
t_objs		*shape_hit(t_ray *ray, t_scene *scene, double t_min, double t_max);
double		get_dist(t_ray *ray, t_objs *shape);
int			compute_rays(t_scene *scene, t_data *data, t_ray *ray,
				t_vec *matrix);

#endif
