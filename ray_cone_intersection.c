/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:04:42 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:46:47 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

static int		satisfies(t_ray ray, t_cone cone, double t)
{
	t_vector	point;
	t_vector	cp;
	double		cp_norm;
	double		cos_angle;

	point = vector_sum(ray.origin, vector_scalar_mul(ray.direction, t));
	cp = vector_sub(point, cone.tip);
	cp_norm = norm(cp);
	cos_angle = cos(cone.angle);
	if (dot(normalize(cp), normalize(cone.direction)) < 0.)
		return (0);
	if (cp_norm > cone.height / cos_angle)
		return (0);
	return (1);
}

static void		set_normal_and_uv(t_ray ray, t_cone cone, double t,
	t_intersection *res)
{
	t_vector	point;
	t_vector	v;
	double		angle;

	angle = cos(cone.angle);
	point = vector_sum(ray.origin, vector_scalar_mul(ray.direction, t));
	v = vector_sum(cone.tip,
		vector_scalar_mul(
			cone.direction,
			norm(vector_sub(point, cone.tip)) / angle));
	res->normal = normalize(vector_sub(point, v));
	res->uv.v = norm(vector_sub(point, cone.tip)) /
		(cone.height / angle);
	point = vector_sum(cone.tip,
				vector_scalar_mul(normalize(vector_sub(point, cone.tip)),
					cone.height / angle));
	v = vector_scalar_mul(cone.direction, cone.height);
	v = normalize(vector_sub(point, vector_sum(cone.tip, v)));
	angle = acos(dot(v, cone.radius_vector));
	if (dot(v, cross(cone.radius_vector, cone.direction)) < 0)
		angle = angle + (M_PI - angle) * 2;
	res->uv.u = angle / M_PI / 2.;
}

t_intersection	simplified_ray_cone_intersection(t_ray ray, t_cone cone)
{
	t_intersection			res;
	t_quadratic_equation	eq;
	t_vector				co;
	double					t[2];

	res = new_intersection();
	co = vector_sub(ray.origin, cone.tip);
	eq.a = dot(ray.direction, cone.direction) *
		dot(ray.direction, cone.direction) -
		cos(cone.angle) * cos(cone.angle);
	eq.b = 2 * (dot(ray.direction, cone.direction) *
		dot(co, cone.direction) - dot(ray.direction, co) *
		cos(cone.angle) * cos(cone.angle));
	eq.c = dot(co, cone.direction) * dot(co, cone.direction) -
		dot(co, co) * cos(cone.angle) * cos(cone.angle);
	if (!solve_quadratic_equation(eq, &t[0], &t[1]))
		return (res);
	if (t[0] < 0. || !satisfies(ray, cone, t[0]))
		t[0] = t[1];
	if (t[0] < 0. || !satisfies(ray, cone, t[0]))
		return (res);
	res.z = t[0];
	return (res);
}

t_intersection	ray_cone_intersection(t_ray ray, t_cone cone)
{
	t_intersection			res;
	t_quadratic_equation	eq;
	t_vector				co;
	double					t[2];

	res = new_intersection();
	co = vector_sub(ray.origin, cone.tip);
	eq.a = dot(ray.direction, cone.direction) *
		dot(ray.direction, cone.direction) -
		cos(cone.angle) * cos(cone.angle);
	eq.b = 2 * (dot(ray.direction, cone.direction) *
		dot(co, cone.direction) - dot(ray.direction, co) *
		cos(cone.angle) * cos(cone.angle));
	eq.c = dot(co, cone.direction) * dot(co, cone.direction) -
		dot(co, co) * cos(cone.angle) * cos(cone.angle);
	if (!solve_quadratic_equation(eq, &t[0], &t[1]))
		return (res);
	if (t[0] < 0. || !satisfies(ray, cone, t[0]))
		t[0] = t[1];
	if (t[0] < 0. || !satisfies(ray, cone, t[0]))
		return (res);
	res.z = t[0];
	set_normal_and_uv(ray, cone, t[0], &res);
	return (res);
}
