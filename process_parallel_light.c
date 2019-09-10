/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parallel_light.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:25:37 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:48:01 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

static int	obstructed(t_ray light_ray, t_scene scene, double light_distance)
{
	t_intersection	intersection;

	intersection = simplified_scene_intersection(scene, light_ray);
	if (intersection.z > 0. && intersection.z < light_distance)
	{
		return (1);
	}
	return (0);
}

void		process_parallel_light(t_lighting lighting, t_lightsource light,
	double *diffuse, double *specular)
{
	t_ray	reflection;
	t_ray	light_ray;

	*diffuse = 0.;
	*specular = 0.;
	if (dot(lighting.normal, light.direction) < 0.)
		return ;
	light_ray.direction = vector_scalar_mul(light.direction, -1.);
	light_ray.origin = vector_sum(lighting.point,
		vector_scalar_mul(light_ray.direction, EPSILON));
	if (obstructed(light_ray, *lighting.scene, 1. / 0.))
		return ;
	*diffuse = light.intensity * dot(lighting.normal, light.direction);
	light_ray.origin = vector_sum(lighting.point,
		vector_scalar_mul(light_ray.direction, 1.));
	light_ray.direction = light.direction;
	reflection = reflected_ray(lighting.intersection.normal, light_ray, 1.);
	*specular = light.intensity * powf(fmax(0., dot(reflection.direction,
		vector_scalar_mul(lighting.view_direction, -1.))),
			lighting.specular_exponent);
}
