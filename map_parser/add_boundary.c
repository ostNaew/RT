/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_boundary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:52:37 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/08 16:25:25 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	add_boundary_values(t_json json, t_sphere *sphere)
{
	t_json		property;
	double		radius;
	t_vector	center;

	property = json_value_by_key(json, "radius");
	if (property.type != JSON_NUMBER || property.value.number <= 0)
		return (-1);
	radius = (double)property.value.number;
	*sphere = new_sphere(radius, (t_vector){0, 0, 0, 0}, 0.);
	property = json_value_by_key(json, "center");
	if (property.type != JSON_OBJECT && property.type != JSON_ARRAY)
		return (-1);
	center = json2vec(property, 1);
	if (!is_valid_vector(center))
		return (-1);
	sphere->center = center;
	return (0);
}

int	add_boundary(t_object *object, t_json json)
{
	t_json	property;

	property = json_value_by_key(json, "boundary");
	if (property.type != JSON_OBJECT && property.type != JSON_NULL)
		return (-1);
	if (property.type == JSON_NULL)
	{
		object->bounded = 0;
		return (0);
	}
	if (add_boundary_values(property, &object->boundary))
		return (-1);
	object->bounded = 1;
	return (0);
}
