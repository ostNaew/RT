/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_view_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 19:42:11 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:20:50 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

t_4x4matrix	ray_view_matrix(t_ray ray)
{
	t_4x4matrix	translation;
	t_4x4matrix	rotation;
	t_vector	view_axis;

	view_axis = (t_vector){0., 0., -1., 0.};
	ray.direction = normalize(ray.direction);
	translation = get_translation_matrix(vector_scalar_mul(ray.origin, -1.));
	rotation = get_rotation_matrix_arbitrary(
					normalize(cross(ray.direction, view_axis)),
					-vectors_angle(ray.direction, view_axis));
	return (matrix_mul(translation, rotation));
}
