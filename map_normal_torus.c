/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normal_torus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:14:00 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/29 21:17:02 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

void	map_normal_torus(t_intersection *inter, t_ray ray)
{
	t_4x4matrix	new_basis;
	t_vector	y_axis;
	t_vector	z_axis;
	t_vector	color;
	t_vector	point;

	point = vector_sum(ray.origin, vector_scalar_mul(ray.direction, inter->z));
	point = vector_sub(point, ((t_torus*)inter->primitive->primitive)->center);
	point = vector_matrix_mul(point,
			((t_torus*)inter->primitive->primitive)->matrix);
	point.z = 0.;
	point.w = 0.;
	y_axis = vector_matrix_mul((t_vector){0, 0, 1, 0},
			((t_torus*)inter->primitive->primitive)->matrix);
	if (norm(point) < ((t_torus*)inter->primitive->primitive)->rt)
		y_axis = vector_scalar_mul(y_axis, -1);
	z_axis = normalize(inter->normal);
	y_axis = normalize(cross(cross(y_axis, z_axis), z_axis));
	new_basis = change_basis_matrix(y_axis, z_axis, (t_vector){0, 0, 0, 1});
	color = get_normal_uv(inter->primitive, inter->uv);
	inter->mapped_normal = normalize(vector_matrix_mul(color, new_basis));
}
