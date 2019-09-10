/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane_triangle_circle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:03:25 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/13 15:21:05 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	get_new_triangle(t_triangle *triangle, t_json json)
{
	t_json			property;
	double			x_cathetus;
	double			y_cathetus;

	property = json_value_by_key(json, "x_cathetus");
	if (property.type != JSON_NUMBER)
		return (-1);
	x_cathetus = (double)property.value.number;
	property = json_value_by_key(json, "y_cathetus");
	if (property.type != JSON_NUMBER)
		return (-1);
	y_cathetus = (double)property.value.number;
	*triangle = new_triangle(x_cathetus, y_cathetus);
	return (0);
}

int	get_transform_triangle(t_triangle *triangle, t_json json)
{
	t_json		property;
	t_4x4matrix	rotation;
	t_vector	position;

	property = json_value_by_key(json, "rotation");
	if (get_rotation_matrix(property, &rotation))
		return (-1);
	property = json_value_by_key(json, "position");
	position = json2vec(property, 0);
	if (!is_valid_vector(position))
		return (-1);
	if (get_new_triangle(triangle, json))
		return (-1);
	*triangle = transform_triangle_ws(*triangle, rotation);
	*triangle = move_triangle(*triangle, position);
	return (0);
}

int	add_planes_values(void **primitive, t_primitive_type type, t_json json)
{
	t_json			property;
	t_triangle		triangle;

	if (get_transform_triangle(&triangle, json))
		return (-1);
	if (type == PLANE || type == TRIANGLE)
	{
		*primitive = malloc(sizeof(t_triangle));
		if (*primitive == NULL)
			return (-1);
		((t_triangle*)(*primitive))[0] = triangle;
	}
	if (type == CIRCLE)
	{
		*primitive = malloc(sizeof(t_circle));
		if (*primitive == NULL)
			return (-1);
		((t_circle*)(*primitive))[0].plane = triangle;
		property = json_value_by_key(json, "radius");
		if (property.type != JSON_NUMBER || property.value.number <= 0.)
			return (-1);
		((t_circle*)(*primitive))[0].radius = (double)property.value.number;
	}
	return (0);
}
