/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:52:38 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:41:27 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracing.h"

static t_ray	bsdf(t_intersection inter, t_ray ray,
	t_vector *signal)
{
	double	chance;

	chance = rand_double();
	if (fits_probability(chance, inter.primitive->material, ALBEDO))
		albedo_ray(&ray, inter, signal);
	else if (fits_probability(chance, inter.primitive->material, SPECULAR))
		specular_ray(&ray, inter, signal);
	else if (fits_probability(chance, inter.primitive->material, REFRACTION))
		refraction_ray(&ray, inter, signal);
	else
	{
		*signal = (t_vector){0., 0., 0., 0.};
		ray.direction = (t_vector){0., 0., 0., 0.};
	}
	return (ray);
}

t_vector		emit(t_render *render, t_intersection inter, t_ray ray)
{
	t_vector	res[2];
	double		intensity[2];

	res[0] = vector_scalar_mul(primitive_color(inter.primitive, inter.uv, 1.),
			inter.primitive->material->light_intensity);
	if (!(inter.primitive->material->light_intensity < 1.))
		return (res[0]);
	get_lighting(ray, inter, render, intensity);
	intensity[0] = intensity[0] * inter.primitive->material->albedo +
		intensity[1];
	res[1] = primitive_color(inter.primitive, inter.uv, intensity[0]);
	return (vector_sum(res[0], res[1]));
}

t_vector		scaled_by(t_vector vector, t_vector scaler)
{
	vector.x *= scaler.x;
	vector.y *= scaler.y;
	vector.z *= scaler.z;
	return (vector);
}

t_vector		trace_path(t_render *render, t_ray ray, size_t depth)
{
	t_vector		signal;
	t_intersection	inter;
	t_vector		res;
	size_t			i;

	res = (t_vector){0., 0., 0., 0.};
	signal = (t_vector){1., 1., 1., 0.};
	i = -1;
	while (++i < depth)
	{
		inter = scene_intersection(render->scene, ray);
		if (!(inter.z > 0. && inter.z < INFINITY))
			return (res);
		res = vector_sum(res, scaled_by(emit(render, inter, ray), signal));
		ray = bsdf(inter, ray, &signal);
	}
	return (res);
}
