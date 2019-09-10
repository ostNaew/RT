/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normal_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:51:07 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:49:43 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

void	map_normal_sphere(t_intersection *inter)
{
	t_4x4matrix	new_basis;
	t_vector	y_axis;
	t_vector	z_axis;
	t_vector	color;

	z_axis = normalize(inter->normal);
	y_axis = normalize(cross(
			cross(((t_sphere*)inter->primitive->primitive)->radius_vector0,
				z_axis),
			z_axis));
	new_basis = change_basis_matrix(y_axis, z_axis, (t_vector){0, 0, 0, 1});
	color = get_normal_uv(inter->primitive, inter->uv);
	inter->mapped_normal = normalize(vector_matrix_mul(color, new_basis));
}
