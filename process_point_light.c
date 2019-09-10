/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_point_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:14:57 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/29 21:18:35 by ejommy           ###   ########.fr       */
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

void		process_point_light(t_lighting lighting, t_lightsource light,
	double *diffuse, double *specular)
{
	t_ray	reflection;
	t_ray	light_ray;

	*diffuse = 0.;
	*specular = 0.;
	light_ray.direction = vector_sub(lighting.point, light.position);
	if (dot(lighting.normal, light_ray.direction) < 0.)
		return ;
	lighting.light_distance = norm(light_ray.direction);
	lighting.light_distance = lighting.light_distance - 0.000001;
	light_ray.direction = normalize(light_ray.direction);
	light_ray.origin = light.position;
	if (obstructed(light_ray, *(lighting.scene), lighting.light_distance))
		return ;
	*diffuse = light.intensity * dot(lighting.normal, light_ray.direction);
	reflection = reflected_ray(lighting.normal, light_ray,
			lighting.light_distance);
	if (lighting.specular_exponent > 0.)
		*specular = light.intensity *
			powf(fmax(0., dot(reflection.direction,
							vector_scalar_mul(lighting.view_direction, -1.))),
					lighting.specular_exponent);
	else
		*specular = 0.;
}
