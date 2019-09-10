/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_circle_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:27:20 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:47:10 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

static t_uv		get_uv(t_vector cp, t_triangle plane, double len, double radius)
{
	t_uv	res;
	double	a0;
	double	a1;

	a0 = dot(cp, normalize(vector_sub(plane.a, plane.b)));
	a1 = dot(cp, vector_sub(plane.a, plane.c));
	res.u = (radius - len * a0) / radius / 2.;
	res.v = (radius -
			(len * sin(acos(a0)) * (a1 < 0. ? -1. : 1.))) / 2. / radius;
	return (res);
}

t_intersection	simplified_ray_circle_intersection(t_ray ray, t_circle circle)
{
	t_intersection	res;
	t_vector		point;
	t_vector		cp;
	double			len;

	res = simplified_ray_plane_intersection(ray, circle.plane);
	point = vector_sum(ray.origin,
				vector_scalar_mul(ray.direction, res.z));
	cp = vector_sub(point, circle.plane.a);
	len = norm2(cp);
	if (len > circle.radius * circle.radius)
	{
		res.z = 1. / 0.;
		return (res);
	}
	return (res);
}

t_intersection	ray_circle_intersection(t_ray ray, t_circle circle)
{
	t_intersection	res;
	t_vector		point;
	t_vector		cp;
	double			len;

	res = simplified_ray_plane_intersection(ray, circle.plane);
	point = vector_sum(ray.origin,
				vector_scalar_mul(ray.direction, res.z));
	cp = vector_sub(point, circle.plane.a);
	len = norm2(cp);
	if (len > circle.radius * circle.radius)
	{
		res.z = 1. / 0.;
		return (res);
	}
	res.normal = normalize(cross(
					vector_sub(circle.plane.b, circle.plane.a),
					vector_sub(circle.plane.c, circle.plane.a)));
	cp = normalize(cp);
	res.uv = get_uv(cp, circle.plane, sqrt(len), circle.radius);
	return (res);
}
