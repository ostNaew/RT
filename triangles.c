/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 18:52:02 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/10 17:14:53 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_triangle	new_triangle(double x_cathetus, double y_cathetus)
{
	t_triangle res;

	res.a = (t_vector){0, 0, 0, 1};
	res.b = (t_vector){x_cathetus, 0, 0, 1};
	res.c = (t_vector){0, y_cathetus, 0, 1};
	return (res);
}

t_triangle	move_triangle(t_triangle triangle, t_vector vector)
{
	triangle.a = vector_sum(triangle.a, vector);
	triangle.b = vector_sum(triangle.b, vector);
	triangle.c = vector_sum(triangle.c, vector);
	return (triangle);
}

t_triangle	rotate_triangle_os(t_triangle triangle, double x_angle,
	double y_angle, double z_angle)
{
	t_4x4matrix	rotation;
	t_vector	translation;

	rotation = matrix_mul(
					matrix_mul(
						get_rotation_matrix_arbitrary(
							normalize(cross(
								vector_sub(triangle.b, triangle.a),
								vector_sub(triangle.c, triangle.a))), z_angle),
						get_rotation_matrix_arbitrary(
							vector_sub(triangle.c, triangle.a), y_angle)),
					get_rotation_matrix_arbitrary(
						vector_sub(triangle.b, triangle.a), x_angle));
	translation = triangle.a;
	triangle.a = vector_sub(triangle.a, translation);
	triangle.b = vector_sub(triangle.c, translation);
	triangle.c = vector_sub(triangle.b, translation);
	triangle.a = vector_matrix_mul(triangle.a, rotation);
	triangle.b = vector_matrix_mul(triangle.b, rotation);
	triangle.c = vector_matrix_mul(triangle.c, rotation);
	triangle.a = vector_sum(triangle.a, translation);
	triangle.b = vector_sum(triangle.c, translation);
	triangle.c = vector_sum(triangle.b, translation);
	return (triangle);
}

t_triangle	transform_triangle_ws(t_triangle triangle, t_4x4matrix matrix)
{
	triangle.a = vector_matrix_mul(triangle.a, matrix);
	triangle.b = vector_matrix_mul(triangle.b, matrix);
	triangle.c = vector_matrix_mul(triangle.c, matrix);
	return (triangle);
}
