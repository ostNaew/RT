/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_torus_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:31:25 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/29 14:53:32 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

double			torus_distance(t_vector point, t_torus torus)
{
	double	len1;
	double	len2;
	double	len3;

	point = vector_sub(point, torus.center);
	point = vector_matrix_mul(point, torus.matrix);
	len1 = sqrt(point.x * point.x + point.y * point.y) - torus.rt;
	len2 = sqrt(len1 * len1 + point.z * point.z);
	len3 = len2 - torus.rc;
	return (len3);
}

t_vector		torus_normal(t_torus torus, t_ray ray, double z)
{
	t_vector	p;
	t_vector	pm;
	t_vector	pp;

	p = vector_sum(ray.origin, vector_scalar_mul(ray.direction, z));
	pm.x = torus_distance((t_vector){p.x - EPSILON, p.y, p.z, 0}, torus);
	pm.y = torus_distance((t_vector){p.x, p.y - EPSILON, p.z, 0}, torus);
	pm.z = torus_distance((t_vector){p.x, p.y, p.z - EPSILON, 0}, torus);
	pp.x = torus_distance((t_vector){p.x + EPSILON, p.y, p.z, 0}, torus);
	pp.y = torus_distance((t_vector){p.x, p.y + EPSILON, p.z, 0}, torus);
	pp.z = torus_distance((t_vector){p.x, p.y, p.z + EPSILON, 0}, torus);
	return (normalize(vector_sub(pp, pm)));
}

t_uv			torus_uv(t_torus torus, t_ray ray, double z)
{
	t_vector	p;
	t_uv		res;
	double		c;

	p = vector_sum(ray.origin, vector_scalar_mul(ray.direction, z));
	p = vector_sub(p, torus.center);
	p = vector_matrix_mul(p, torus.matrix);
	res.u = 0.5 + atan2(p.y, p.x) / 2 / M_PI;
	c = p.x * p.x + p.y * p.y;
	c = pow(c, 0.5) - torus.rt;
	res.v = 0.5 + atan2(p.z, c) / 2 / M_PI;
	return (res);
}

t_intersection	simplified_ray_torus_intersection(t_ray ray, t_torus torus)
{
	t_intersection	res;
	t_vector		point;
	double			dist_tmp;
	double			dist;

	res = new_intersection();
	dist_tmp = 1. / 0.;
	point = ray.origin;
	while (1)
	{
		dist = fabs(torus_distance(point, torus));
		point = vector_sum(point,
				vector_scalar_mul(ray.direction, dist));
		if (dist <= EPSILON || (dist > dist_tmp && dist > torus.rt + torus.rc))
			break ;
		dist_tmp = dist;
	}
	if (dist <= EPSILON)
		res.z = norm(vector_sub(point, ray.origin));
	return (res);
}

t_intersection	ray_torus_intersection(t_ray ray, t_torus torus)
{
	t_intersection	res;

	res = simplified_ray_torus_intersection(ray, torus);
	res.normal = torus_normal(torus, ray, res.z);
	res.uv = torus_uv(torus, ray, res.z);
	return (res);
}
