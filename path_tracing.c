/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:01:30 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 21:07:10 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

static void	get_rays(t_ray *rays, t_camera camera, int width, int height)
{
	int			i;
	int			n_rays;
	t_4x4matrix	rotation;
	t_vector	point[2];

	i = -1;
	n_rays = width * height;
	rotation = matrix_mul(
			get_rotation_matrix_x(-camera.polar_angle),
			get_rotation_matrix_z(-camera.azimuthal_angle));
	point[0] = rand_vec_in_hemisphere((t_vector){0., 1., 0., 0.});
	point[0].y = 0.;
	point[0] = vector_scalar_mul(point[0], camera.lens_radius);
	point[1] = vector_sum(vector_matrix_mul(point[0], rotation),
			camera.position);
	point[0] = vector_scalar_mul(point[0], -1);
	while (++i < n_rays)
	{
		rays[i].direction = normalize(vector_matrix_mul(
			vector_sum((t_vector){-(i % width - width / 2),
				camera.focus, -(i / width - height / 2), 0.}, point[0]),
			rotation));
		rays[i].origin = point[1];
	}
}

void		path_tracing(t_render *render)
{
	int			i;

	i = -1;
	get_rays(render->rays, render->camera,
			render->window_width, render->window_height);
	while (++i < render->window_width * render->window_height &&
			render->path_tracing)
	{
		render->pixels[i].color = vector_sum(render->pixels[i].color,
				trace_path(render, render->rays[i], 5));
		render->pixels[i].divider += 1;
	}
}
