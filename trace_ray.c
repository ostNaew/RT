/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:37:25 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:39:58 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

static t_vector	result_color(t_intersection intersection, t_vector *colors,
	double *intensity)
{
	colors[2] = vector_scalar_mul(primitive_color(intersection.primitive,
			intersection.uv, intensity[0]),
		intersection.primitive->material->albedo);
	colors[3] = primitive_color(
			intersection.primitive, intersection.uv, intensity[1]);
	colors[4] = primitive_color(intersection.primitive, intersection.uv,
			intersection.primitive->material->light_intensity);
	return (vector_sum(
				vector_sum(
					vector_sum(colors[0], colors[1]),
					vector_sum(colors[2], colors[3])),
				colors[4]));
}

t_vector		trace_ray(t_render *render, t_ray ray, size_t depth)
{
	t_intersection	intersection;
	t_ray			sub_ray;
	t_vector		colors[5];
	double			intensity[2];

	colors[0] = (t_vector){0., 0., 0., 0.};
	colors[1] = (t_vector){0., 0., 0., 0.};
	intersection = scene_intersection(render->scene, ray);
	if (intersection.z < 0. || intersection.z == 1. / 0.)
		return (colors[1]);
	get_lighting(ray, intersection, render, intensity);
	if (depth)
	{
		sub_ray = reflected_ray(intersection.normal, ray, intersection.z);
		if (intersection.primitive->material->specular > 0.)
			colors[0] = vector_scalar_mul(trace_ray(render, sub_ray, depth - 1),
				intersection.primitive->material->specular);
		sub_ray = refracted_ray(intersection, ray,
			intersection.primitive->material->refractive_index, 1.);
		if (intersection.primitive->material->refraction > 0.)
			colors[1] = vector_scalar_mul(trace_ray(render, sub_ray, depth - 1),
				intersection.primitive->material->refraction);
	}
	return (result_color(intersection, colors, intensity));
}
