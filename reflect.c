/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 12:23:46 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/15 17:39:23 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_ray	reflected_ray(t_vector normal, t_ray ray, double z)
{
	t_ray	res;

	if (dot(normal, ray.direction) > 0)
		normal = vector_scalar_mul(normal, -1.);
	res.origin = vector_sum(ray.origin,
			vector_scalar_mul(ray.direction, z));
	res.direction = normalize(vector_sub(
			ray.direction,
			vector_scalar_mul(
				normal,
				2. * dot(ray.direction, normal))));
	res.origin = vector_sum(
			res.origin,
			vector_scalar_mul(normal, EPSILON));
	return (res);
}
