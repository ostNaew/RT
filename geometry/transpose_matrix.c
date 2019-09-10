/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:23:13 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/28 17:11:54 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

t_4x4matrix	transpose_matrix(t_4x4matrix matrix)
{
	size_t		i;
	size_t		j;
	t_4x4matrix	res;

	i = -1;
	res = matrix;
	while (++i < 4 && (j = -1))
		while (++j < 4)
		{
			if (i == j)
				j++;
			if (j == 4)
				break ;
			res.value[i][j] = matrix.value[j][i];
		}
	return (res);
}
