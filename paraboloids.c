/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloids.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 16:21:04 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/29 19:36:51 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

t_paraboloid	new_paraboloid(double height, double k)
{
	return ((t_paraboloid){
			.position = (t_vector){0, 0, 0, 1},
			.direction = (t_vector){0, 0, 1, 0},
			.vecr = (t_vector){-1, 0, 0, 0},
			.height = height,
			.k = k});
}

t_paraboloid	move_paraboloid(t_paraboloid paraboloid, t_vector vector)
{
	paraboloid.position = vector_sum(paraboloid.position, vector);
	return (paraboloid);
}

t_paraboloid	transform_paraboloid_ws(t_paraboloid paraboloid,
					t_4x4matrix matrix)
{
	paraboloid.position = vector_matrix_mul(paraboloid.position, matrix);
	paraboloid.direction = normalize(
					vector_matrix_mul(paraboloid.direction, matrix));
	paraboloid.vecr = normalize(
		vector_matrix_mul(paraboloid.vecr, matrix));
	return (paraboloid);
}
