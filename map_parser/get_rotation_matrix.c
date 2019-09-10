/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rotation_matrix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:12:54 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/08 19:06:31 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	get_rotation_matrix(t_json json, t_4x4matrix *rotation)
{
	t_json		prop;
	t_vector	angles;

	*rotation = identity_matrix();
	if (json.type != JSON_OBJECT && json.type != JSON_NULL)
		return (-1);
	if (json.type == JSON_NULL)
		return (0);
	prop = json_value_by_key(json, "x");
	if (prop.type != JSON_NUMBER && prop.type != JSON_NULL)
		return (-1);
	angles.x = (prop.type == JSON_NUMBER ? (double)prop.value.number : 0.);
	prop = json_value_by_key(json, "y");
	if (prop.type != JSON_NUMBER && prop.type != JSON_NULL)
		return (-1);
	angles.y = (prop.type == JSON_NUMBER ? (double)prop.value.number : 0.);
	prop = json_value_by_key(json, "z");
	if (prop.type != JSON_NUMBER && prop.type != JSON_NULL)
		return (-1);
	angles.z = (prop.type == JSON_NUMBER ? (double)prop.value.number : 0.);
	*rotation = matrix_mul(get_rotation_matrix_x(angles.x * M_PI / 180.),
			get_rotation_matrix_y(angles.y * M_PI / 180.));
	*rotation = matrix_mul(*rotation,
			get_rotation_matrix_z(angles.z * M_PI / 180.));
	return (0);
}
