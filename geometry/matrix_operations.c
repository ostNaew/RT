/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 20:36:40 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/09 14:51:08 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

t_4x4matrix	matrix_mul(t_4x4matrix matrix1, t_4x4matrix matrix2)
{
	t_4x4matrix res;
	unsigned	i;
	unsigned	j;

	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 4)
			res.value[i][j] = matrix1.value[i][0] * matrix2.value[0][j] +
								matrix1.value[i][1] * matrix2.value[1][j] +
								matrix1.value[i][2] * matrix2.value[2][j] +
								matrix1.value[i][3] * matrix2.value[3][j];
	return (res);
}

t_4x4matrix	matrix_sum(t_4x4matrix matrix1, t_4x4matrix matrix2)
{
	unsigned	i;
	unsigned	j;

	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 4)
			matrix1.value[i][j] += matrix2.value[i][j];
	return (matrix1);
}

t_4x4matrix	matrix_scalar_mul(t_4x4matrix matrix, double number)
{
	unsigned	i;
	unsigned	j;

	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 4)
			matrix.value[i][j] *= number;
	return (matrix);
}
