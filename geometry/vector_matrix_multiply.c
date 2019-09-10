/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_matrix_multiply.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 18:45:04 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:21:25 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

t_vector	vector_matrix_mul(t_vector vector,
	t_4x4matrix matrix)
{
	t_vector res;

	res.x = matrix.value[0][0] * vector.x +
			matrix.value[1][0] * vector.y +
			matrix.value[2][0] * vector.z +
			matrix.value[3][0] * vector.w;
	res.y = matrix.value[0][1] * vector.x +
			matrix.value[1][1] * vector.y +
			matrix.value[2][1] * vector.z +
			matrix.value[3][1] * vector.w;
	res.z = matrix.value[0][2] * vector.x +
			matrix.value[1][2] * vector.y +
			matrix.value[2][2] * vector.z +
			matrix.value[3][2] * vector.w;
	res.w = matrix.value[0][3] * vector.x +
			matrix.value[1][3] * vector.y +
			matrix.value[2][3] * vector.z +
			matrix.value[3][3] * vector.w;
	return (res);
}

t_vector	matrix_vector_mul(t_4x4matrix matrix,
	t_vector vector)
{
	t_vector res;

	res.x = matrix.value[0][0] * vector.x +
			matrix.value[0][1] * vector.y +
			matrix.value[0][2] * vector.z +
			matrix.value[0][3] * vector.w;
	res.y = matrix.value[1][0] * vector.x +
			matrix.value[1][1] * vector.y +
			matrix.value[1][2] * vector.z +
			matrix.value[1][3] * vector.w;
	res.z = matrix.value[2][0] * vector.x +
			matrix.value[2][1] * vector.y +
			matrix.value[2][2] * vector.z +
			matrix.value[2][3] * vector.w;
	res.w = matrix.value[3][0] * vector.x +
			matrix.value[3][1] * vector.y +
			matrix.value[3][2] * vector.z +
			matrix.value[3][3] * vector.w;
	return (res);
}
