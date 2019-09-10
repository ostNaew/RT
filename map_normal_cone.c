/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normal_cone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 14:58:41 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/10 21:30:41 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

void	map_normal_cone(t_intersection *inter)
{
	t_4x4matrix	new_basis;
	t_vector	y_axis;
	t_vector	z_axis;

	z_axis = inter->normal;
	y_axis = cross(
		cross(
			vector_scalar_mul(
				((t_cone*)inter->primitive->primitive)->direction, -1.),
			z_axis),
		z_axis);
	new_basis = change_basis_matrix(y_axis, z_axis, (t_vector){0, 0, 0, 0});
	inter->mapped_normal = vector_matrix_mul(
			get_normal_uv(inter->primitive, inter->uv), new_basis);
}
