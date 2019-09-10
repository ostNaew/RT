/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_path_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:38:54 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:17:57 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracing.h"

int		fits_probability(double probability, t_material *material,
	t_probability_type type)
{
	if (type == ALBEDO)
		return (probability < material->albedo);
	else if (type == SPECULAR)
		return (probability < (material->albedo + material->specular));
	else
		return (probability <=
				(material->albedo + material->specular + material->refraction));
}

void	albedo_ray(t_ray *ray, t_intersection intersection, t_vector *signal)
{
	t_vector	color;

	color = primitive_color(intersection.primitive, intersection.uv, 1.);
	signal->x *= color.x * intersection.primitive->material->albedo;
	signal->y *= color.y * intersection.primitive->material->albedo;
	signal->z *= color.z * intersection.primitive->material->albedo;
	if (dot(ray->direction, intersection.normal) > 0.)
	{
		intersection.normal = vector_scalar_mul(intersection.normal, -1);
		intersection.mapped_normal =
			vector_scalar_mul(intersection.mapped_normal, -1);
	}
	ray->origin = vector_sum(
		ray->origin, vector_scalar_mul(ray->direction, intersection.z));
	ray->direction = normalize(
		rand_vec_in_hemisphere(intersection.mapped_normal));
	ray->origin = vector_sum(ray->origin,
		vector_scalar_mul(intersection.normal, EPSILON));
}

double	lerps(double start, double end, double percent)
{
	double p;

	p = 1. - percent;
	return (start * p + end * percent);
}

void	specular_ray(t_ray *ray, t_intersection intersection, t_vector *signal)
{
	t_vector	color;

	color = primitive_color(intersection.primitive, intersection.uv, 1.);
	signal->x *= color.x * intersection.primitive->material->specular;
	signal->y *= color.y * intersection.primitive->material->specular;
	signal->z *= color.z * intersection.primitive->material->specular;
	*ray = reflected_ray(intersection.mapped_normal, *ray, intersection.z);
}

void	refraction_ray(t_ray *ray, t_intersection intersection,
	t_vector *signal)
{
	t_vector	color;

	color = primitive_color(intersection.primitive, intersection.uv, 1.);
	signal->x *= color.x * intersection.primitive->material->refraction;
	signal->y *= color.y * intersection.primitive->material->refraction;
	signal->z *= color.z * intersection.primitive->material->refraction;
	*ray = refracted_ray(intersection, *ray,
			intersection.primitive->material->refractive_index, 1.);
}
