/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:43:42 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:17:51 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

double			rand_double(void)
{
	return ((double)rand() / (double)RAND_MAX);
}

t_vector		rand_vec_in_hemisphere(t_vector normal)
{
	t_vector	res;

	res = (t_vector){
		.x = rand_double() - .5,
		.y = rand_double() - .5,
		.z = rand_double() - .5,
		.w = 0.};
	if (dot(res, normal) < 0)
		res = vector_scalar_mul(res, -1.);
	return (res);
}

t_intersection	new_intersection(void)
{
	return ((t_intersection){
			.primitive = NULL,
			.normal = (t_vector){0., 0., 0., 0.},
			.uv = (t_uv){0., 0.},
			.z = 1. / 0.});
}

t_material		normalize_material(t_material material)
{
	double	l;

	if (material.albedo + material.specular +
			material.refraction + material.emittance <= 1.0)
		return (material);
	l = sqrt(material.albedo * material.albedo +
			material.specular * material.specular +
			material.refraction * material.refraction +
			material.emittance * material.emittance);
	material.albedo /= l;
	material.specular /= l;
	material.refraction /= l;
	material.emittance /= l;
	material.albedo *= material.albedo;
	material.specular *= material.specular;
	material.refraction *= material.refraction;
	material.emittance *= material.emittance;
	return (material);
}

double			limit(double num, double bottom, double upper)
{
	if (num < bottom)
		return (bottom);
	else if (num > upper)
		return (upper);
	return (num);
}
