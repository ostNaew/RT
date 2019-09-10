/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_intersection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:54:22 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:46:22 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

static void		set_normal_and_uv(t_ray ray, t_cylinder cylinder, double t,
	t_intersection *res)
{
	t_vector	point;
	t_vector	position_at_height;
	double		angle;
	double		height;

	point = vector_sum(ray.origin,
			vector_scalar_mul(ray.direction, t));
	angle = dot(
			normalize(vector_sub(point, cylinder.position)),
			cylinder.direction);
	height = norm(vector_sub(point, cylinder.position)) * angle;
	position_at_height = vector_sum(cylinder.position,
		vector_scalar_mul(cylinder.direction, height));
	res->normal = normalize(vector_sub(position_at_height, point));
	res->uv.v = height / cylinder.height;
	angle = acos(dot(res->normal, normalize(cylinder.radius_vector)));
	if (dot(res->normal,
			cross(cylinder.radius_vector, cylinder.direction)) < 0)
		angle = angle + (M_PI - angle) * 2;
	res->uv.u = angle / 2. / M_PI;
}

static int		point_too_far(t_ray ray, double t, t_cylinder cyl)
{
	t_vector	point;
	t_vector	center;
	double		half_height;

	half_height = cyl.height / 2.;
	point = vector_sum(ray.origin, vector_scalar_mul(ray.direction, t));
	center = vector_sum(cyl.position,
			vector_scalar_mul(cyl.direction, half_height));
	return (norm2(vector_sub(point, center)) >
		(cyl.radius * cyl.radius + half_height * half_height));
}

t_intersection	simplified_ray_cylinder_intersection(t_ray ray, t_cylinder cyl)
{
	t_intersection			res;
	t_vector				xy[2];
	double					t[3];
	t_quadratic_equation	eq;

	xy[0] = cross(vector_sub(ray.origin, cyl.position), cyl.direction);
	xy[1] = cross(ray.direction, cyl.direction);
	t[2] = dot(cyl.direction, cyl.direction) * cyl.radius * cyl.radius;
	eq.a = dot(xy[1], xy[1]);
	eq.b = 2 * dot(xy[0], xy[1]);
	eq.c = dot(xy[0], xy[0]) - t[2];
	res = new_intersection();
	if (solve_quadratic_equation(eq, &t[0], &t[1]))
	{
		if (t[0] < 0. || point_too_far(ray, t[0], cyl))
			t[0] = t[1];
		if (t[0] < 0. || point_too_far(ray, t[0], cyl))
			return (res);
		res.z = t[0];
	}
	return (res);
}

t_intersection	ray_cylinder_intersection(t_ray ray, t_cylinder cyl)
{
	t_intersection			res;
	t_vector				xy[2];
	double					t[3];
	t_quadratic_equation	eq;

	xy[0] = cross(vector_sub(ray.origin, cyl.position), cyl.direction);
	xy[1] = cross(ray.direction, cyl.direction);
	t[2] = dot(cyl.direction, cyl.direction) * cyl.radius * cyl.radius;
	eq.a = dot(xy[1], xy[1]);
	eq.b = 2 * dot(xy[0], xy[1]);
	eq.c = dot(xy[0], xy[0]) - t[2];
	res = new_intersection();
	if (solve_quadratic_equation(eq, &t[0], &t[1]))
	{
		if (t[0] < 0. || point_too_far(ray, t[0], cyl))
			t[0] = t[1];
		if (t[0] < 0. || point_too_far(ray, t[0], cyl))
			return (res);
		set_normal_and_uv(ray, cyl, t[0], &res);
		res.z = t[0];
	}
	return (res);
}
