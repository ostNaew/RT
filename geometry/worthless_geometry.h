/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 18:36:14 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 16:06:24 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORTHLESS_GEOMETRY_H
# define WORTHLESS_GEOMETRY_H

# include <math.h>
# include <string.h>
# include <stdlib.h>

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_vector;

typedef struct	s_4x4matrix
{
	double	value[4][4];
}				t_4x4matrix;

typedef struct	s_triangle
{
	t_vector	a;
	t_vector	b;
	t_vector	c;
}				t_triangle;

typedef struct	s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct	s_quadratic_equation
{
	double	a;
	double	b;
	double	c;
}				t_quadratic_equation;

typedef struct	s_plane_equation
{
	double	a;
	double	b;
	double	c;
	double	d;
}				t_plane_equation;

typedef struct	s_sphere
{
	t_vector	center;
	t_vector	radius_vector0;
	t_vector	radius_vector1;
	t_vector	truncation_vector;
	double		truncation_angle;
	double		radius;
}				t_sphere;

typedef struct	s_cylinder
{
	t_vector	position;
	t_vector	direction;
	t_vector	radius_vector;
	double		height;
	double		radius;
}				t_cylinder;

typedef struct	s_cone
{
	t_vector	tip;
	t_vector	direction;
	t_vector	radius_vector;
	double		height;
	double		angle;
}				t_cone;

typedef struct	s_circle
{
	t_triangle	plane;
	double		radius;
}				t_circle;

typedef struct	s_paraboloid
{
	t_vector	position;
	t_vector	direction;
	double		k;
	double		height;
	t_vector	vecr;
}				t_paraboloid;

typedef struct	s_torus
{
	t_vector	center;
	t_4x4matrix	matrix;
	double		rt;
	double		rc;
}				t_torus;

t_4x4matrix		matrix_mul(t_4x4matrix matrix1, t_4x4matrix matrix2);
t_4x4matrix		matrix_sum(t_4x4matrix matrix1, t_4x4matrix matrix2);
t_4x4matrix		matrix_scalar_mul(t_4x4matrix matrix, double number);
t_4x4matrix		invert_matrix(t_4x4matrix matrix);
t_4x4matrix		get_rotation_matrix_x(double angle);
t_4x4matrix		get_rotation_matrix_y(double angle);
t_4x4matrix		get_rotation_matrix_z(double angle);
t_4x4matrix		get_rotation_matrix_arbitrary(t_vector axis, double angle);
t_4x4matrix		get_translation_matrix(t_vector vector);
t_4x4matrix		get_scale_matrix(double x, double y, double z);
t_4x4matrix		identity_matrix(void);
t_4x4matrix		change_basis_matrix(t_vector y, t_vector z, t_vector pos);
t_4x4matrix		ray_view_matrix(t_ray ray);
t_4x4matrix		transpose_matrix(t_4x4matrix matrix);
t_4x4matrix		invert_matrix(t_4x4matrix matrix);

double			vectors_angle(t_vector v1, t_vector v2);
double			dot(t_vector v1, t_vector v2);
double			norm(t_vector v);
double			norm2(t_vector v);
t_vector		vector_matrix_mul(t_vector vector, t_4x4matrix matrix);
t_vector		matrix_vector_mul(t_4x4matrix matrix, t_vector vector);
t_vector		cross(t_vector v1, t_vector v2);
t_vector		vector_scalar_mul(t_vector vector, double number);
t_vector		normalize(t_vector vector);
t_vector		vector_sum(t_vector v1, t_vector v2);
t_vector		vector_sub(t_vector v1, t_vector v2);
int				is_valid_vector(t_vector vector);

int				point_in_triangle_2d(t_triangle triangle, t_vector point);

int				solve_quadratic_equation(t_quadratic_equation equation,
					double *t0, double *t1);

#endif
