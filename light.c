/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:15:30 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/24 13:17:12 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

static void	init_lighting(t_lighting *lighting, t_ray view_ray,
		t_intersection intersection, t_render *render)
{
	lighting->scene = &(render->scene);
	lighting->view_direction = view_ray.direction;
	lighting->normal = intersection.mapped_normal;
	lighting->specular_exponent =
		intersection.primitive->material->specular_exponent;
	if (dot(intersection.normal, view_ray.direction) < 0.)
		lighting->normal = vector_scalar_mul(lighting->normal, -1.);
	lighting->point = vector_sum(view_ray.origin,
			vector_scalar_mul(view_ray.direction, intersection.z));
}

static void	process_lightsource(t_lighting lighting, t_lightsource light,
		double *intensity)
{
	intensity[0] = 0.;
	intensity[1] = 0.;
	if (light.type == AMBIENT)
		intensity[0] += light.intensity;
	else if (light.type == POINT)
		process_point_light(lighting, light, &intensity[0], &intensity[1]);
	else if (light.type == DIRECTIONAL)
		process_directional_light(lighting, light,
				&intensity[0], &intensity[1]);
	else if (light.type == PARALLEL)
		process_parallel_light(lighting, light, &intensity[0], &intensity[1]);
}

void		get_lighting(t_ray view_ray, t_intersection intersection,
		t_render *render, double *res_intensity)
{
	t_lighting		lighting;
	unsigned short	i;
	double			intensity[2];
	double			tmp_intensity[2];

	init_lighting(&lighting, view_ray, intersection, render);
	lighting.intersection = intersection;
	i = -1;
	intensity[0] = 0.;
	intensity[1] = 0.;
	while (++i < render->n_lights)
	{
		process_lightsource(lighting, render->lights[i], tmp_intensity);
		intensity[0] += fmax(0., tmp_intensity[0]);
		intensity[1] += fmax(0., tmp_intensity[1]);
	}
	if (intensity[0] > 1.)
		intensity[0] = 1.;
	res_intensity[0] = intensity[0];
	res_intensity[1] = intensity[1];
}
