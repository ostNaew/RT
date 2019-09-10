/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:00:20 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 15:52:11 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_intersection	simplified_ray_primitive_intersection(t_ray r,
	t_primitive *p)
{
	t_intersection	res;

	res.z = 1. / 0.;
	if (p->type == TRIANGLE)
		res = simplified_ray_triangle_intersection(r,
				*((t_triangle*)p->primitive));
	else if (p->type == SPHERE)
		res = simplified_ray_sphere_intersection(r, *((t_sphere*)p->primitive));
	else if (p->type == CYLINDER)
		res = simplified_ray_cylinder_intersection(r,
				*((t_cylinder*)p->primitive));
	else if (p->type == CIRCLE)
		res = simplified_ray_circle_intersection(r, *((t_circle*)p->primitive));
	else if (p->type == CONE)
		res = simplified_ray_cone_intersection(r, *((t_cone*)p->primitive));
	else if (p->type == PLANE)
		res = simplified_ray_plane_intersection(r,
				*((t_triangle*)p->primitive));
	else if (p->type == PARABOLOID)
		res = simplified_ray_paraboloid_intersection(r,
				*((t_paraboloid*)p->primitive));
	else if (p->type == TORUS)
		res = simplified_ray_torus_intersection(r, *((t_torus*)p->primitive));
	res.primitive = p;
	return (res);
}

t_intersection	ray_primitive_intersection(t_ray ray,
	t_primitive *primitive)
{
	t_intersection	res;

	res.z = 1. / 0.;
	if (primitive->type == TRIANGLE)
		res = ray_triangle_intersection(ray,
				*((t_triangle*)primitive->primitive));
	else if (primitive->type == SPHERE)
		res = ray_sphere_intersection(ray, *((t_sphere*)primitive->primitive));
	else if (primitive->type == CYLINDER)
		res = ray_cylinder_intersection(ray,
				*((t_cylinder*)primitive->primitive));
	else if (primitive->type == CIRCLE)
		res = ray_circle_intersection(ray, *((t_circle*)primitive->primitive));
	else if (primitive->type == CONE)
		res = ray_cone_intersection(ray, *((t_cone*)primitive->primitive));
	else if (primitive->type == PLANE)
		res = ray_plane_intersection(ray, *((t_triangle*)primitive->primitive));
	else if (primitive->type == PARABOLOID)
		res = ray_paraboloid_intersection(ray,
				*((t_paraboloid*)primitive->primitive));
	else if (primitive->type == TORUS)
		res = ray_torus_intersection(ray, *((t_torus*)primitive->primitive));
	res.primitive = primitive;
	return (res);
}
