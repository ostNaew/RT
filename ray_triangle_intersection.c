/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_triangle_intersection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 13:35:42 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/13 17:08:35 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_intersection	simplified_ray_triangle_intersection(t_ray ray,
	t_triangle triangle)
{
	t_intersection	res;
	t_vector		vector[5];
	double			det;
	double			inv_det;

	vector[0] = vector_sub(triangle.b, triangle.a);
	vector[1] = vector_sub(triangle.c, triangle.a);
	vector[2] = cross(ray.direction, vector[1]);
	res.z = -1. / 0.;
	det = dot(vector[0], vector[2]);
	if (det < 1e-8 && det > -1e-8)
		return (res);
	inv_det = 1. / det;
	vector[3] = vector_sub(ray.origin, triangle.a);
	res.uv.u = dot(vector[3], vector[2]) * inv_det;
	if (res.uv.u < 0. || res.uv.u > 1.)
		return (res);
	vector[4] = cross(vector[3], vector[0]);
	res.uv.v = dot(ray.direction, vector[4]) * inv_det;
	if (res.uv.v < 0. || res.uv.u + res.uv.v > 1.)
		return (res);
	res.z = dot(vector[1], vector[4]) * inv_det;
	return (res);
}

t_intersection	ray_triangle_intersection(t_ray ray, t_triangle triangle)
{
	t_intersection	res;
	t_vector		vector[5];
	double			det;
	double			inv_det;

	vector[0] = vector_sub(triangle.b, triangle.a);
	vector[1] = vector_sub(triangle.c, triangle.a);
	vector[2] = cross(ray.direction, vector[1]);
	res.z = -1. / 0.;
	det = dot(vector[0], vector[2]);
	if (det < 1e-8 && det > -1e-8)
		return (res);
	inv_det = 1. / det;
	vector[3] = vector_sub(ray.origin, triangle.a);
	res.uv.u = dot(vector[3], vector[2]) * inv_det;
	if (res.uv.u < 0. || res.uv.u > 1.)
		return (res);
	vector[4] = cross(vector[3], vector[0]);
	res.uv.v = dot(ray.direction, vector[4]) * inv_det;
	if (res.uv.v < 0. || res.uv.u + res.uv.v > 1.)
		return (res);
	res.normal = normalize(cross(vector[0], vector[1]));
	res.z = dot(vector[1], vector[4]) * inv_det;
	return (res);
}
