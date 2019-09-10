/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normal_paraboloid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 19:08:31 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/29 19:44:48 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

void	map_normal_paraboloid(t_intersection *inter)
{
	t_4x4matrix	new_basis;
	t_vector	y_axis;
	t_vector	z_axis;
	t_vector	color;

	z_axis = normalize(inter->normal);
	y_axis = normalize(cross(cross(vector_scalar_mul(
				((t_paraboloid*)inter->primitive->primitive)->direction, -1),
				z_axis), z_axis));
	new_basis = change_basis_matrix(y_axis, z_axis, (t_vector){0, 0, 0, 1});
	color = get_normal_uv(inter->primitive, inter->uv);
	inter->mapped_normal = normalize(vector_matrix_mul(color, new_basis));
}
