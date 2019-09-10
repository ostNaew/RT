/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:36:47 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/10 21:17:48 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_sphere	new_sphere(double radius, t_vector truncation_vector,
	double truncation_angle)
{
	return ((t_sphere){
			.center = (t_vector){0, 0, 0, 1},
			.radius = radius,
			.radius_vector0 = (t_vector){0, 0, 1, 0},
			.radius_vector1 = (t_vector){0, 1, 0, 0},
			.truncation_vector = truncation_vector,
			.truncation_angle = truncation_angle});
}

t_sphere	move_sphere(t_sphere sphere, t_vector vector)
{
	sphere.center = vector_sum(sphere.center, vector);
	return (sphere);
}

t_sphere	rotate_sphere_os(t_sphere sphere, double x_angle, double y_angle,
	double z_angle)
{
	t_4x4matrix	rotation;

	rotation = matrix_mul(
					matrix_mul(
						get_rotation_matrix_arbitrary(
							normalize(
								cross(
									sphere.radius_vector0,
									sphere.radius_vector1)),
							x_angle),
						get_rotation_matrix_arbitrary(sphere.radius_vector1,
							y_angle)),
					get_rotation_matrix_arbitrary(sphere.radius_vector0,
						z_angle));
	sphere.radius_vector0 = vector_matrix_mul(sphere.radius_vector0, rotation);
	sphere.radius_vector1 = vector_matrix_mul(sphere.radius_vector1, rotation);
	sphere.truncation_vector = vector_matrix_mul(sphere.truncation_vector,
		rotation);
	return (sphere);
}

t_sphere	transform_sphere_ws(t_sphere sphere, t_4x4matrix matrix)
{
	sphere.center = vector_matrix_mul(sphere.center, matrix);
	sphere.radius_vector0 = normalize(
		vector_matrix_mul(sphere.radius_vector0, matrix));
	sphere.radius_vector1 = normalize(
		vector_matrix_mul(sphere.radius_vector1, matrix));
	sphere.truncation_vector = normalize(
		vector_matrix_mul(sphere.truncation_vector, matrix));
	return (sphere);
}
