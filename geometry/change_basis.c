/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_basis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:59:14 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/09 14:50:59 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

t_4x4matrix	change_basis_matrix(t_vector y, t_vector z, t_vector pos)
{
	t_4x4matrix translation;
	t_4x4matrix	rotation;
	t_vector	x;

	translation = get_translation_matrix(vector_scalar_mul(pos, -1.));
	rotation = identity_matrix();
	x = normalize(cross(y, z));
	rotation.value[0][0] = x.x;
	rotation.value[0][1] = x.y;
	rotation.value[0][2] = x.z;
	rotation.value[1][0] = y.x;
	rotation.value[1][1] = y.y;
	rotation.value[1][2] = y.z;
	rotation.value[2][0] = z.x;
	rotation.value[2][1] = z.y;
	rotation.value[2][2] = z.z;
	return (matrix_mul(translation, rotation));
}
