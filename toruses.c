/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toruses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:26:04 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/30 20:33:19 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_torus	new_torus(double rt, double rc)
{
	t_4x4matrix	m;

	m = identity_matrix();
	return ((t_torus){
			.center = (t_vector){0, 0, 0, 1},
			.matrix = m,
			.rt = rt,
			.rc = rc});
}

t_torus	move_torus(t_torus torus, t_vector vector)
{
	torus.center = vector_sum(torus.center, vector);
	return (torus);
}

t_torus	transform_torus_ws(t_torus torus, t_4x4matrix matrix)
{
	torus.center = vector_matrix_mul(torus.center, matrix);
	torus.matrix = invert_matrix(matrix_mul(
				invert_matrix(torus.matrix), matrix));
	return (torus);
}
