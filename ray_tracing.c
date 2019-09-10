/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:02:14 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 20:26:34 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

static void	get_rays(t_ray *rays, t_camera camera, int width, int height)
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

void		ray_tracing(t_render *render)
{
	int			i;

	i = -1;
	clear_pixels_buffer(render);
	get_rays(render->rays, render->camera,
			render->window_width, render->window_height);
	while (++i < render->window_width * render->window_height &&
			render->path_tracing == 0)
	{
		render->pixels[i].color = vector_sum(
				render->pixels[i].color,
				trace_ray(render, render->rays[i], 5));
		render->pixels[i].divider += 1;
	}
}
