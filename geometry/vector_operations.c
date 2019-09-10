/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 20:44:40 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/09 14:51:33 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

double		dot(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector	cross(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	res.w = 0.;
	return (res);
}

t_vector	vector_scalar_mul(t_vector vector, double number)
{
	vector.x *= number;
	vector.y *= number;
	vector.z *= number;
	return (vector);
}

t_vector	normalize(t_vector vector)
{
	double	lenght;

	lenght = norm2(vector);
	if (lenght != 1. && lenght != 0.)
	{
		lenght = sqrt(lenght);
		vector.x /= lenght;
		vector.y /= lenght;
		vector.z /= lenght;
	}
	return (vector);
}

t_vector	vector_sum(t_vector v1, t_vector v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}
