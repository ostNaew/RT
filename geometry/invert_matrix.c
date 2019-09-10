/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invert_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 13:59:36 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/28 18:07:36 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

static double	det3x3(double *m)
{
	double	det;

	det = m[0] * m[4] * m[8] + m[6] * m[1] * m[5] + m[3] * m[7] * m[2] -
		m[6] * m[4] * m[2] - m[0] * m[7] * m[5] - m[3] * m[1] * m[8];
	free(m);
	return (det);
}

static double	*matrix3x3(t_4x4matrix m, size_t index)
{
	double	*res;
	size_t	i;
	size_t	j;
	size_t	x;
	size_t	y;

	x = -1;
	i = -1;
	res = malloc(sizeof(double) * 9);
	while (++i < 3 && ++x < 4)
	{
		y = -1;
		j = -1;
		while (++j < 3 && ++y < 4)
		{
			if (x == index / 4)
				x++;
			if (y == index % 4)
				y++;
			if (x < 4 && y < 4)
				res[i * 3 + j] = m.value[x][y];
		}
	}
	return (res);
}

static double	det4x4(t_4x4matrix m)
{
	double	d[4];
	size_t	i;
	double	res;

	i = -1;
	while (++i < 4)
		d[i] = det3x3(matrix3x3(m, i));
	res = m.value[0][0] * d[0] - m.value[0][1] * d[1] +
		m.value[0][2] * d[2] - m.value[0][3] * d[3];
	return (res);
}

t_4x4matrix		invert_matrix(t_4x4matrix matrix)
{
	double		d;
	size_t		i;
	size_t		j;
	t_4x4matrix	res;

	d = det4x4(matrix);
	if (!d)
		return (matrix);
	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 4)
		{
			res.value[i][j] = det3x3(matrix3x3(matrix, i * 4 + j));
			if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
				res.value[i][j] *= -1;
		}
	res = transpose_matrix(res);
	res = matrix_scalar_mul(res, 1. / d);
	return (res);
}
