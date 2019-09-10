/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:35:57 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/23 16:41:06 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_cone	new_cone(double height, double angle)
{
	return ((t_cone){
			.tip = (t_vector){0, 0, 0, 1},
			.direction = (t_vector){0, 0, -1, 0},
			.radius_vector = (t_vector){-1, 0, 0, 0},
			.height = height,
			.angle = angle});
}

t_cone	move_cone(t_cone cone, t_vector vector)
{
	cone.tip = vector_sum(cone.tip, vector);
	return (cone);
}

t_cone	rotate_cone_os(t_cone cone, double x_angle, double y_angle,
	double z_angle)
{
	t_4x4matrix	rotation;
	t_vector	translation;

	translation = vector_sub(cone.tip,
			(t_vector){0., 0., cone.height / 2., 1.});
	rotation = matrix_mul(
					matrix_mul(
						get_rotation_matrix_arbitrary(
							normalize(
								cross(
									cone.radius_vector,
									cone.direction)),
							y_angle),
						get_rotation_matrix_arbitrary(cone.radius_vector,
							x_angle)),
					get_rotation_matrix_arbitrary(cone.direction,
						-z_angle));
	cone.tip = vector_sub(cone.tip, translation);
	cone.tip = vector_matrix_mul(cone.tip, rotation);
	cone.tip = vector_sum(cone.tip, translation);
	cone.direction = vector_matrix_mul(cone.direction, rotation);
	cone.radius_vector = vector_matrix_mul(cone.radius_vector, rotation);
	return (cone);
}

t_cone	transform_cone_ws(t_cone cone, t_4x4matrix matrix)
{
	cone.tip = vector_matrix_mul(cone.tip, matrix);
	cone.direction = normalize(vector_matrix_mul(cone.direction, matrix));
	cone.radius_vector = normalize(
		vector_matrix_mul(cone.radius_vector, matrix));
	return (cone);
}
