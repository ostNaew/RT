/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:38:46 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/17 16:49:23 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_ray	refracted_ray(t_intersection inter, t_ray ray,
	double eta_t, double eta_i)
{
	double	cosi;
	double	eta;
	double	k;
	t_ray	res;

	cosi = -fmax(-1., fmin(1., dot(ray.direction, inter.normal)));
	if (cosi < 0)
	{
		inter.normal = vector_scalar_mul(inter.normal, -1.);
		return (refracted_ray(inter, ray, eta_i, eta_t));
	}
	eta = eta_i / eta_t;
	k = 1 - eta * eta * (1 - cosi * cosi);
	if (k < 0)
		res.direction = (t_vector){0., 0., 0., 0.};
	else
		res.direction = normalize(vector_sum(
			vector_scalar_mul(ray.direction, eta),
			vector_scalar_mul(inter.normal, (eta * cosi - sqrt(k)))));
	res.origin = vector_sum(
		vector_sum(ray.origin, vector_scalar_mul(ray.direction, inter.z)),
		vector_scalar_mul(res.direction, EPSILON));
	return (res);
}
