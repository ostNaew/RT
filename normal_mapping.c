/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:14:44 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/29 20:39:18 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_vector	get_normal_uv(t_primitive *primitive, t_uv uv)
{
	t_vector	res;

	res = color2vec(get_color_uv(primitive->normal_map, uv));
	res.x -= 0.5;
	res.y -= 0.5;
	res.z -= 0.5;
	return (normalize(res));
}

void		map_normal(t_intersection *inter, t_ray ray)
{
	if (inter->primitive->normal_map.image)
	{
		if (inter->primitive->type == TRIANGLE)
			map_normal_triangle(inter);
		else if (inter->primitive->type == PLANE)
			map_normal_plane(inter);
		else if (inter->primitive->type == SPHERE)
			map_normal_sphere(inter);
		if (inter->primitive->type == CYLINDER)
			map_normal_cylinder(inter);
		if (inter->primitive->type == CIRCLE)
			map_normal_circle(inter);
		if (inter->primitive->type == CONE)
			map_normal_cone(inter);
		if (inter->primitive->type == TORUS)
			map_normal_torus(inter, ray);
		if (inter->primitive->type == PARABOLOID)
			map_normal_paraboloid(inter);
	}
	else
		inter->mapped_normal = inter->normal;
}
