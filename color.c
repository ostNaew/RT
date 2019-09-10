/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:14:12 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:52:59 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

int			vec2color(t_vector vector)
{
	int	res;

	vector.x = vector.x > 1. ? 1. : vector.x;
	vector.y = vector.y > 1. ? 1. : vector.y;
	vector.z = vector.z > 1. ? 1. : vector.z;
	if (vector.x < 0.)
		vector.x = 0.;
	if (vector.y < 0.)
		vector.y = 0.;
	if (vector.z < 0.)
		vector.z = 0.;
	res = (((int)(vector.x * 255.)) << 16) |
		(((int)(vector.y * 255.)) << 8) |
		((int)(vector.z * 255.));
	return (res);
}

t_vector	color2vec(int color)
{
	t_vector	res;

	res.x = (double)((color >> 16) & 0xff);
	res.y = (double)((color >> 8) & 0xff);
	res.z = (double)(color & 0xff);
	res = vector_scalar_mul(res, 1. / 255.);
	return (res);
}

t_vector	primitive_color(t_primitive *primitive, t_uv uv, double lighting)
{
	int	color;

	if (lighting > 0.)
	{
		color = get_color_uv(primitive->texture, uv);
		return (vector_scalar_mul(color2vec(color), lighting));
	}
	return (color2vec(0x0));
}
