/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:13:27 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/13 15:21:57 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	get_sphere(t_json json, t_sphere *sphere)
{
	t_json		property;
	double		radius;
	double		truncation_angle;
	t_vector	truncation_vector;

	property = json_value_by_key(json, "radius");
	if (property.type != JSON_NUMBER || property.value.number <= 0)
		return (-1);
	radius = (double)property.value.number;
	property = json_value_by_key(json, "truncation_angle");
	if ((property.type != JSON_NUMBER || property.value.number < 0) &&
			property.type != JSON_NULL)
		return (-1);
	truncation_angle = property.type == JSON_NULL ? 0. / 0. :
		(double)property.value.number * M_PI / 180.;
	property = json_value_by_key(json, "truncation_vector");
	truncation_vector = property.type == JSON_NULL ?
		(t_vector){0, 0, 0, 0} : json2vec(property, 0);
	if (!is_valid_vector(truncation_vector))
		return (-1);
	*sphere = new_sphere(radius, truncation_vector, truncation_angle);
	return (0);
}

int	transform_sphere(t_json json, t_sphere *sphere)
{
	t_json		property;
	t_vector	center;
	t_4x4matrix	rotation;

	property = json_value_by_key(json, "center");
	center = json2vec(property, 1);
	if (!is_valid_vector(center))
		return (-1);
	property = json_value_by_key(json, "rotation");
	if (get_rotation_matrix(property, &rotation))
		return (-1);
	*sphere = transform_sphere_ws(*sphere, rotation);
	sphere->center = center;
	return (0);
}

int	add_spheres_values(void **primitive, t_json json)
{
	t_sphere	sphere;

	if (get_sphere(json, &sphere))
		return (-1);
	if (transform_sphere(json, &sphere))
		return (-1);
	*primitive = malloc(sizeof(t_sphere));
	((t_sphere*)(*primitive))[0] = sphere;
	return (0);
}
