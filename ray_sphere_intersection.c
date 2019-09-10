/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 14:41:50 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:46:07 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

static int		satisifies(t_ray ray, t_sphere sphere, double t)
{
	t_vector	point;

	point = vector_sum(ray.origin, vector_scalar_mul(ray.direction, t));
	point = vector_sub(point, sphere.center);
	if (!isnan(sphere.truncation_angle) &&
		vectors_angle(point, sphere.truncation_vector) >
			sphere.truncation_angle)
		return (0);
	return (1);
}

static void		set_normal_and_uv(t_ray ray, t_sphere sphere,
	t_intersection *res)
{
	t_vector				normal;

	res->normal = normalize(vector_sub(vector_sum(ray.origin,
		vector_scalar_mul(ray.direction, res->z)), sphere.center));
	res->uv.v = (acos(dot(res->normal, sphere.radius_vector0))) / M_PI;
	normal = vector_matrix_mul(res->normal, get_rotation_matrix_arbitrary(
		cross(sphere.radius_vector0, res->normal),
		acos(dot(res->normal, sphere.radius_vector0)) - M_PI / 2.));
	res->uv.u = acos(dot(normal, sphere.radius_vector1));
	res->uv.u = (res->uv.u +
		(dot(normal, cross(sphere.radius_vector1, sphere.radius_vector0)) < 0 ?
		(M_PI - res->uv.u) * 2. : 0.)) / M_PI / 2.;
}

t_intersection	simplified_ray_sphere_intersection(t_ray ray, t_sphere sphere)
{
	t_intersection			res;
	t_quadratic_equation	eq;
	double					roots[2];

	res = new_intersection();
	eq.a = 1.;
	eq.b = 2. * (dot(vector_sub(ray.origin, sphere.center), ray.direction));
	eq.c = dot(vector_sub(ray.origin, sphere.center),
		vector_sub(ray.origin, sphere.center)) - sphere.radius * sphere.radius;
	if (!solve_quadratic_equation(eq, &roots[0], &roots[1]))
		return (res);
	if (roots[0] < 0. || !satisifies(ray, sphere, roots[0]))
		roots[0] = roots[1];
	if (roots[0] < 0. || !satisifies(ray, sphere, roots[0]))
		return (res);
	res.z = roots[0];
	return (res);
}

t_intersection	ray_sphere_intersection(t_ray ray, t_sphere sphere)
{
	t_intersection			res;
	t_quadratic_equation	eq;
	double					roots[2];

	res = new_intersection();
	eq.a = 1.;
	eq.b = 2. * (dot(vector_sub(ray.origin, sphere.center), ray.direction));
	eq.c = dot(vector_sub(ray.origin, sphere.center),
		vector_sub(ray.origin, sphere.center)) - sphere.radius * sphere.radius;
	if (!solve_quadratic_equation(eq, &roots[0], &roots[1]))
		return (res);
	if (roots[0] < 0. || !satisifies(ray, sphere, roots[0]))
		roots[0] = roots[1];
	if (roots[0] < 0. || !satisifies(ray, sphere, roots[0]))
		return (res);
	res.z = roots[0];
	set_normal_and_uv(ray, sphere, &res);
	return (res);
}
