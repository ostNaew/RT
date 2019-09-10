/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_render.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:11:14 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 16:11:25 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_RENDER_H
# define ENGINE_RENDER_H

# include <time.h>
# include <float.h>
# include <stdlib.h>
# include <stdio.h>
# include <SDL.h>
# include "worthless_geometry.h"
# include "libft.h"
# include "netpbm.h"
# include "json.h"
# include "dyad.h"

# include <fcntl.h>

# define WINDOW_WIDTH 300
# define WINDOW_HEIGHT 300
# define WINDOW_FULLSCREEN_WIDTH 5120
# define WINDOW_FULLSCREEN_HEIGHT 2880
# define EPSILON 1e-8
# define PROCESSING_THREADS 8

typedef uint64_t	t_hash;
t_hash			siphash24(const void *src, unsigned long src_sz,
					const char key[16]);
typedef struct s_task	t_task;

typedef enum	e_primitive_type
{
	PLANE,
	SPHERE,
	CYLINDER,
	CIRCLE,
	CONE,
	TRIANGLE,
	PARABOLOID,
	TORUS
}				t_primitive_type;

typedef enum	e_light_type
{
	AMBIENT,
	POINT,
	DIRECTIONAL,
	PARALLEL
}				t_light_type;

typedef enum	e_network_mode
{
	STANDALONE,
	MASTER,
	SLAVE
}				t_network_mode;

typedef struct	s_pixel
{
	t_vector	color;
	size_t		divider;
}				t_pixel;

typedef struct	s_texture
{
	t_netpbm_image	*image;
	int				color;
	char			inv_vert;
	char			inv_hor;
}				t_texture;

typedef struct	s_camera
{
	t_vector	position;
	double		lens_radius;
	double		polar_angle;
	double		azimuthal_angle;
	double		focus;
	double		view_angle;
}				t_camera;

typedef struct	s_uv
{
	double	u;
	double	v;
}				t_uv;

typedef struct	s_lightsource
{
	t_vector		position;
	t_vector		direction;
	double			angle;
	double			intensity;
	t_light_type	type;
}				t_lightsource;

typedef struct	s_material
{
	double		emittance;
	double		light_intensity;
	double		albedo;
	double		specular;
	double		specular_exponent;
	double		refraction;
	double		refractive_index;
}				t_material;

typedef struct	s_primitive
{
	void				*primitive;
	t_texture			texture;
	t_texture			normal_map;
	t_material			*material;
	t_primitive_type	type;
}				t_primitive;

typedef struct	s_object
{
	t_sphere		boundary;
	t_primitive		*primitives;
	size_t			n_primitives;
	char			bounded;
}				t_object;

typedef struct	s_intersection
{
	t_primitive	*primitive;
	t_vector	normal;
	t_vector	mapped_normal;
	t_uv		uv;
	double		z;
}				t_intersection;

typedef struct	s_scene
{
	t_object	*objects;
	size_t		n_objects;
}				t_scene;

typedef struct	s_render
{
	SDL_Window		*window;
	SDL_Surface		*image;
	t_camera		camera;
	t_scene			scene;
	t_pixel			*pixels;
	t_ray			*rays;
	t_lightsource	*lights;
	size_t			n_lights;
	t_material		*materials;
	size_t			n_materials;
	t_netpbm_image	*images;
	size_t			n_images;
	char			*map_str;
	t_network_mode	mode;
	dyad_Stream		*stream;
	int				working;
	t_task			*task;
	int				window_width;
	int				window_height;
	char			render_needed;
	char			refresh_needed;
	char			rendering;
	char			path_tracing;
	char			autosave;
	unsigned		last_save_time;
	char			*location;
}				t_render;

typedef struct	s_filter
{
	t_vector		(*filter)(t_vector *, size_t);
	size_t			size;
}				t_filter;

void			main_loop(t_render *render);
void			slave_main_loop(t_render *render);
void			clear_pixels_buffer(t_render *render);
void			path_tracing(t_render *render);
void			ray_tracing(t_render *render);

int				render_thread(void *data);
int				refresh_thread(void *data);

void			save_intermediate_result(t_render *render);
void			load_intermediate_result(t_render *render);

int				process_map(t_render *render, t_json json, int load_images);
char			*read_map(char *filename);
int				check_images(t_render *render);
void			networking(t_render *render);

int				movement_key_hook(SDL_Event *e, t_render *render);
int				filters_key_hook(SDL_Event *event, t_render *render);
int				camera_rotation_key_hook(SDL_Event *event, t_render *render);

/*
**HELPERS
*/

t_intersection	new_intersection(void);
double			rand_double(void);
t_vector		rand_vec_in_hemisphere(t_vector normal);
t_material		normalize_material(t_material material);
double			limit(double num, double bottom, double upper);

int				init(t_render *render, int argc, char **argv);

t_vector		trace_ray(t_render *render, t_ray ray, size_t depth);
t_vector		trace_path(t_render *render, t_ray ray, size_t depth);

int				get_color_uv(t_texture texture, t_uv uv);
int				vec2color(t_vector vector);
t_vector		color2vec(int color);

t_vector		primitive_color(t_primitive *primitive, t_uv uv,
					double lighting);

t_ray			reflected_ray(t_vector normal, t_ray ray, double z);
t_ray			refracted_ray(t_intersection inter, t_ray ray, double eta_t,
					double eta_i);
t_vector		apply_filters(t_render *render, size_t index);
t_filter		active_filter(size_t i, int resize);
double			get_index_brightness(double scale);

/*
**NETWORK
*/

void			init_network(t_render *render, const char *host, int port);
size_t			get_num_samples_in_task(void);
void			send_result(t_render *render);
void			process_task(t_render *render);

/*
**NORMAL MAPPING
*/

t_vector		get_normal_uv(t_primitive *primitive, t_uv uv);
void			map_normal(t_intersection *inter, t_ray ray);
void			map_normal_triangle(t_intersection *inter);
void			map_normal_sphere(t_intersection *inter);
void			map_normal_plane(t_intersection *inter);
void			map_normal_circle(t_intersection *inter);
void			map_normal_cylinder(t_intersection *inter);
void			map_normal_cone(t_intersection *inter);
void			map_normal_torus(t_intersection *inter, t_ray ray);
void			map_normal_paraboloid(t_intersection *inter);

/*
**INTERSECTION
*/

t_intersection	ray_torus_intersection(t_ray ray, t_torus torus);
t_intersection	simplified_ray_torus_intersection(
					t_ray ray, t_torus torus);

t_intersection	ray_paraboloid_intersection(t_ray ray, t_paraboloid paraboloid);
t_intersection	simplified_ray_paraboloid_intersection(
					t_ray ray, t_paraboloid paraboloid);

t_intersection	scene_intersection(t_scene scene, t_ray ray);
t_intersection	simplified_scene_intersection(t_scene scene, t_ray ray);

t_intersection	ray_primitive_intersection(t_ray ray, t_primitive *primitive);
t_intersection	simplified_ray_primitive_intersection(t_ray ray,
					t_primitive *primitive);

t_intersection	ray_triangle_intersection(t_ray ray, t_triangle triangle);
t_intersection	simplified_ray_triangle_intersection(t_ray ray,
					t_triangle triangle);

t_intersection	ray_sphere_intersection(t_ray ray, t_sphere sphere);
t_intersection	simplified_ray_sphere_intersection(t_ray ray, t_sphere sphere);

t_intersection	ray_cylinder_intersection(t_ray ray, t_cylinder cylinder);
t_intersection	simplified_ray_cylinder_intersection(t_ray ray, t_cylinder cyl);

t_intersection	ray_cone_intersection(t_ray ray, t_cone cone);
t_intersection	simplified_ray_cone_intersection(t_ray ray, t_cone cone);

t_intersection	ray_plane_intersection(t_ray ray, t_triangle triangle);
t_intersection	simplified_ray_plane_intersection(t_ray ray,
					t_triangle triangle);

t_intersection	ray_circle_intersection(t_ray ray, t_circle circle);
t_intersection	simplified_ray_circle_intersection(t_ray ray, t_circle circle);

void			get_lighting(t_ray view_ray, t_intersection intersection,
					t_render *render, double *res_intensity);

/*
**TRIANGLES/PLANES
*/
t_triangle		new_triangle(double x_cathetus, double y_cathetus);
t_triangle		move_triangle(t_triangle triangle, t_vector vector);
t_triangle		rotate_triangle_os(t_triangle triangle, double x_angle,
					double y_angle, double z_angle);
t_triangle		transform_triangle_ws(t_triangle triangle, t_4x4matrix matrix);

/*
**SPHERES
*/
t_sphere		new_sphere(double radius, t_vector truncation_vector,
					double truncation_angle);
t_sphere		move_sphere(t_sphere sphere, t_vector vector);
t_sphere		rotate_sphere_os(t_sphere sphere, double x_angle,
					double y_angle, double z_angle);
t_sphere		transform_sphere_ws(t_sphere sphere, t_4x4matrix matrix);

/*
**CYLINDERS
*/
t_cylinder		new_cylinder(double height, double radius);
t_cylinder		move_cylinder(t_cylinder cylinder, t_vector vector);
t_cylinder		rotate_cylinder_os(t_cylinder cylinder, double x_angle,
					double y_angle, double z_angle);
t_cylinder		transform_cylinder_ws(t_cylinder cylinder, t_4x4matrix matrix);

/*
**CIRCLES
*/
t_circle		new_circle(double radius);
t_circle		move_circle(t_circle circle, t_vector vector);
t_circle		rotate_circle_os(t_circle circle, double x_angle,
					double y_angle, double z_angle);
t_circle		transform_circle_ws(t_circle circle, t_4x4matrix matrix);

/*
**CONES
*/
t_cone			new_cone(double	height, double angle);
t_cone			move_cone(t_cone cone, t_vector vector);
t_cone			rotate_cone_os(t_cone cone, double x_angle, double y_angle,
					double z_angle);
t_cone			transform_cone_ws(t_cone cone, t_4x4matrix matrix);

/*
**PARABOLOIDS
*/
t_paraboloid	move_paraboloid(t_paraboloid paraboloid, t_vector vector);
t_paraboloid	transform_paraboloid_ws(t_paraboloid paraboloid,
					t_4x4matrix matrix);
t_paraboloid	new_paraboloid(double height, double k);

/*
**TORUSES
*/
t_torus			move_torus(t_torus torus, t_vector vector);
t_torus			transform_torus_ws(t_torus torus, t_4x4matrix matrix);
t_torus			new_torus(double height, double k);

#endif
