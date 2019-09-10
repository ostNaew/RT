/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:32:06 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:18:05 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_cylinder	new_cylinder(double height, double radius)
{
	return ((t_cylinder){
			.position = (t_vector){0., 0., -height / 2., 1.},
			.direction = (t_vector){0., 0., 1., 0.},
			.radius_vector = (t_vector){1., 0., 0., 0.},
			.height = height,
			.radius = radius});
}

t_cylinder	move_cylinder(t_cylinder cylinder, t_vector vector)
{
	cylinder.position = vector_sum(cylinder.position, vector);
	return (cylinder);
}

t_cylinder	rotate_cylinder_os(t_cylinder cylinder, double x_angle,
	double y_angle, double z_angle)
{
	t_4x4matrix	rotation;
	t_vector	translation;

	translation = vector_sub(cylinder.position,
			(t_vector){0., 0., -cylinder.height / 2., 1.});
	rotation = matrix_mul(
					matrix_mul(
						get_rotation_matrix_arbitrary(
							normalize(
								cross(
									cylinder.direction,
									cylinder.radius_vector)),
							y_angle),
						get_rotation_matrix_arbitrary(cylinder.radius_vector,
							x_angle)),
					get_rotation_matrix_arbitrary(cylinder.direction,
						z_angle));
	cylinder.position = vector_sub(cylinder.position, translation);
	cylinder.position = vector_matrix_mul(cylinder.position, rotation);
	cylinder.position = vector_sum(cylinder.position, translation);
	cylinder.direction = vector_matrix_mul(cylinder.direction, rotation);
	cylinder.radius_vector = vector_matrix_mul(
			cylinder.radius_vector, rotation);
	return (cylinder);
}

t_cylinder	transform_cylinder_ws(t_cylinder cylinder, t_4x4matrix matrix)
{
	cylinder.position = vector_matrix_mul(cylinder.position, matrix);
	cylinder.direction = normalize(
		vector_matrix_mul(cylinder.direction, matrix));
	cylinder.radius_vector = normalize(
		vector_matrix_mul(cylinder.radius_vector, matrix));
	return (cylinder);
}
