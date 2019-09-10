/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normal_triangle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:34:57 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/22 17:18:34 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

void	map_normal_triangle(t_intersection *inter)
{
	t_triangle	*triangle;
	t_vector	tangent;
	t_4x4matrix	new_basis;
	t_vector	new_normal;

	triangle = (t_triangle*)inter->primitive->primitive;
	tangent = normalize(vector_sub(triangle->c, triangle->a));
	new_basis = change_basis_matrix(
			tangent, inter->normal, (t_vector){0, 0, 0, 0});
	new_normal = get_normal_uv(inter->primitive, inter->uv);
	new_normal = normalize(vector_matrix_mul(new_normal, new_basis));
	inter->mapped_normal = new_normal;
}
