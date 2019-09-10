/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_paraboloid_intersection.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 14:00:07 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/29 21:34:18 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_vector		paraboloid_normal(t_ray ray, t_paraboloid paraboloid, double z)
{
	t_vector	point;
	double		m;
	t_vector	cp;
	t_vector	normal;

	point = vector_sum(ray.origin, vector_scalar_mul(ray.direction, z));
	cp = vector_sub(point, paraboloid.position);
	m = dot(cp, paraboloid.direction);
	normal = normalize(vector_sub(cp,
				vector_scalar_mul(paraboloid.direction, m + paraboloid.k)));
	return (normal);
}

t_uv			paraboloid_uv(t_ray ray, t_paraboloid paraboloid, double z)
{
	t_vector	p[2];
	double		m;
	t_vector	cp;
	t_uv		res;

	p[0] = vector_sum(ray.origin, vector_scalar_mul(ray.direction, z));
	cp = vector_sub(p[0], paraboloid.position);
	m = norm(cp) * dot(normalize(cp), paraboloid.direction);
	res.v = m / paraboloid.height;
	p[1] = vector_sum(paraboloid.position,
			vector_scalar_mul(paraboloid.direction, m));
	cp = normalize(vector_sub(p[0], p[1]));
	m = acos(dot(cp, paraboloid.vecr));
	if (dot(cp, cross(paraboloid.direction, paraboloid.vecr)) < 0)
		m = 2 * M_PI - m;
	res.u = m / 2 / M_PI;
	return (res);
}

static int		satisfies(t_ray ray, t_paraboloid paraboloid, double z)
{
	t_vector	cp;
	t_vector	point;
	double		h;

	point = vector_sum(ray.origin, vector_scalar_mul(ray.direction, z));
	cp = vector_sub(point, paraboloid.position);
	h = norm(cp) * dot(normalize(cp), paraboloid.direction);
	if (h < paraboloid.height)
		return (1);
	return (0);
}

t_intersection	simplified_ray_paraboloid_intersection(
					t_ray ray, t_paraboloid paraboloid)
{
	t_intersection			res;
	t_quadratic_equation	eq;
	t_vector				oc;
	double					t[2];

	res = new_intersection();
	oc = vector_sub(ray.origin, paraboloid.position);
	eq.a = dot(ray.direction, ray.direction) -
		pow(dot(ray.direction, paraboloid.direction), 2);
	eq.b = dot(ray.direction, oc) - dot(ray.direction, paraboloid.direction) *
		(dot(oc, paraboloid.direction) + 2 * paraboloid.k);
	eq.b *= 2;
	eq.c = dot(oc, oc) - dot(oc, paraboloid.direction) *
		(dot(oc, paraboloid.direction) + 4 * paraboloid.k);
	if (!solve_quadratic_equation(eq, &t[0], &t[1]))
		return (res);
	if (t[0] < 0. || !satisfies(ray, paraboloid, t[0]))
		t[0] = t[1];
	if (t[0] < 0. || !satisfies(ray, paraboloid, t[0]))
		return (res);
	res.z = t[0];
	return (res);
}

t_intersection	ray_paraboloid_intersection(t_ray ray, t_paraboloid paraboloid)
{
	t_intersection			res;
	t_quadratic_equation	eq;
	t_vector				oc;
	double					t[2];

	res = new_intersection();
	oc = vector_sub(ray.origin, paraboloid.position);
	eq.a = dot(ray.direction, ray.direction) -
		pow(dot(ray.direction, paraboloid.direction), 2);
	eq.b = dot(ray.direction, oc) - dot(ray.direction, paraboloid.direction) *
		(dot(oc, paraboloid.direction) + 2 * paraboloid.k);
	eq.b *= 2;
	eq.c = dot(oc, oc) - dot(oc, paraboloid.direction) *
		(dot(oc, paraboloid.direction) + 4 * paraboloid.k);
	if (!solve_quadratic_equation(eq, &t[0], &t[1]))
		return (res);
	if (t[0] < 0. || !satisfies(ray, paraboloid, t[0]))
		t[0] = t[1];
	if (t[0] < 0. || !satisfies(ray, paraboloid, t[0]))
		return (res);
	res.z = t[0];
	res.normal = paraboloid_normal(ray, paraboloid, t[0]);
	res.uv = paraboloid_uv(ray, paraboloid, t[0]);
	return (res);
}
