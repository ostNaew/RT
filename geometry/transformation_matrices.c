/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_matrices.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:51:35 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/09 14:51:27 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

t_4x4matrix		get_translation_matrix(t_vector vector)
{
	t_4x4matrix	res;

	res = identity_matrix();
	res.value[3][0] = vector.x;
	res.value[3][1] = vector.y;
	res.value[3][2] = vector.z;
	return (res);
}

t_4x4matrix		get_scale_matrix(double x, double y, double z)
{
	t_4x4matrix	res;

	res = identity_matrix();
	res.value[0][0] = x;
	res.value[1][1] = y;
	res.value[2][2] = z;
	return (res);
}
