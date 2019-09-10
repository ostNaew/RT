/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:47:02 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/16 20:49:32 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

void	get_rays(t_ray *rays, t_camera camera, int width, int height)
{
	int			i;
	int			n_rays;
	t_4x4matrix	rotation;

	i = -1;
	n_rays = width * height;
	rotation = matrix_mul(
			get_rotation_matrix_x(-camera.polar_angle),
			get_rotation_matrix_z(-camera.azimuthal_angle));
	while (++i < n_rays)
	{
		rays[i].origin = camera.position;
		rays[i].direction = normalize(
			vector_matrix_mul(
				(t_vector){
					-(i % width - width / 2),
					camera.focus,
					-(i / width - height / 2),
					0.},
				rotation));
	}
}
