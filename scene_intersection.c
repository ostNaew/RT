/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:08:25 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/29 20:40:26 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

static int		is_nul_vector(t_vector vector)
{
	return (vector.x == 0. && vector.y == 0. && vector.z == 0.);
}

static void		simplified_objects_intersection(t_ray ray, t_object obj,
	t_intersection *res)
{
	t_intersection	tmp;
	size_t			i;

	if (obj.bounded)
		tmp = simplified_ray_sphere_intersection(ray, obj.boundary);
	else
		tmp.z = 1.;
	if (tmp.z > 0 && tmp.z < 1. / 0.)
	{
		i = -1;
		while (++i < obj.n_primitives)
		{
			tmp = simplified_ray_primitive_intersection(ray,
					&obj.primitives[i]);
			if (tmp.z > 0. && tmp.z < res->z)
				*res = tmp;
		}
	}
}

t_intersection	simplified_scene_intersection(t_scene scene, t_ray ray)
{
	t_intersection	res;
	size_t			i;

	res = new_intersection();
	if (is_nul_vector(ray.direction))
		return (res);
	i = -1;
	while (++i < scene.n_objects)
		simplified_objects_intersection(ray, scene.objects[i], &res);
	return (res);
}

t_intersection	scene_intersection(t_scene scene, t_ray ray)
{
	t_intersection	res;

	res = simplified_scene_intersection(scene, ray);
	if (!(res.z > 0. && res.z < 1. / 0.))
		return (res);
	res = ray_primitive_intersection(ray, res.primitive);
	map_normal(&res, ray);
	return (res);
}
