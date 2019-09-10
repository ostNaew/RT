/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:10:52 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/17 15:12:59 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filters.h"

double		*get_matrix_blur(int size)
{
	double	*matrix;
	int		i;
	double	divider;
	double	exp;

	matrix = ft_memalloc(sizeof(double) * size * size);
	i = -1;
	divider = 0.;
	while (matrix && ++i < size * size)
	{
		exp = (pow(i % size - size / 2, 2) + pow(i / size - size / 2, 2)) / 2.0;
		matrix[i] = pow(M_E, -exp) / (2 * M_PI);
		divider += matrix[i];
	}
	i = -1;
	while (matrix && ++i < size * size)
		matrix[i] /= divider;
	return (matrix);
}

t_vector	colors_matrix_mul(t_vector *colors, double *matrix, size_t size)
{
	size_t		i;
	t_vector	color;

	i = -1;
	color = (t_vector){0, 0, 0, 0};
	while (++i < size * size)
		color = vector_sum(color, vector_scalar_mul(colors[i], matrix[i]));
	return (color);
}

t_vector	blur(t_vector *colors, size_t size)
{
	double			*matrix;
	t_vector		res;
	static size_t	static_size;
	static double	*static_matrix;

	if (static_size != size)
	{
		matrix = static_matrix;
		free(matrix);
		static_matrix = get_matrix_blur(size);
		static_size = size;
	}
	res = colors_matrix_mul(colors, static_matrix, static_size);
	return (res);
}
