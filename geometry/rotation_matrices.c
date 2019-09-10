/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrices.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 20:50:57 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:21:06 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worthless_geometry.h"

t_4x4matrix	get_rotation_matrix_x(double angle)
{
	t_4x4matrix res;
	double		angle_sin;
	double		angle_cos;

	res = identity_matrix();
	angle_sin = sin(angle);
	angle_cos = cos(angle);
	res.value[1][1] = angle_cos;
	res.value[1][2] = -angle_sin;
	res.value[2][1] = angle_sin;
	res.value[2][2] = angle_cos;
	return (res);
}

t_4x4matrix	get_rotation_matrix_y(double angle)
{
	t_4x4matrix res;
	double		angle_sin;
	double		angle_cos;

	res = identity_matrix();
	angle_sin = sin(angle);
	angle_cos = cos(angle);
	res.value[0][0] = angle_cos;
	res.value[0][2] = angle_sin;
	res.value[2][0] = -angle_sin;
	res.value[2][2] = angle_cos;
	return (res);
}

t_4x4matrix	get_rotation_matrix_z(double angle)
{
	t_4x4matrix res;
	double		angle_sin;
	double		angle_cos;

	res = identity_matrix();
	angle_sin = sin(angle);
	angle_cos = cos(angle);
	res.value[0][0] = angle_cos;
	res.value[0][1] = -angle_sin;
	res.value[1][0] = angle_sin;
	res.value[1][1] = angle_cos;
	return (res);
}

t_4x4matrix	get_rotation_matrix_arbitrary(t_vector axis, double angle)
{
	t_4x4matrix res;
	double		angle_cos;
	double		angle_sin;
	double		inv_angle_cos;

	angle_cos = cos(angle);
	angle_sin = sin(angle);
	inv_angle_cos = 1. - angle_cos;
	axis = normalize(axis);
	res = identity_matrix();
	res.value[0][0] = angle_cos + inv_angle_cos * axis.x * axis.x;
	res.value[0][1] = inv_angle_cos * axis.x * axis.y - angle_sin * axis.z;
	res.value[0][2] = inv_angle_cos * axis.x * axis.z + angle_sin * axis.y;
	res.value[1][0] = inv_angle_cos * axis.y * axis.x + angle_sin * axis.z;
	res.value[1][1] = angle_cos + inv_angle_cos * axis.y * axis.y;
	res.value[1][2] = inv_angle_cos * axis.y * axis.z - angle_sin * axis.x;
	res.value[2][0] = inv_angle_cos * axis.z * axis.x - angle_sin * axis.y;
	res.value[2][1] = inv_angle_cos * axis.z * axis.y + angle_sin * axis.x;
	res.value[2][2] = angle_cos + inv_angle_cos * axis.z * axis.z;
	return (res);
}
