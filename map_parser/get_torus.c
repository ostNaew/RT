/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_torus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:15:49 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/28 20:07:10 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	get_torus(t_json json, t_torus *torus)
{
	t_json	property;
	double	rt;
	double	rc;

	property = json_value_by_key(json, "rt");
	if (property.type != JSON_NUMBER || property.value.number <= 0)
		return (-1);
	rt = (double)property.value.number;
	property = json_value_by_key(json, "rc");
	if (property.type != JSON_NUMBER || property.value.number <= 0)
		return (-1);
	rc = (double)property.value.number;
	*torus = new_torus(rt, rc);
	return (0);
}

int	transform_torus(t_json json, t_torus *torus)
{
	t_json		property;
	t_vector	center;
	t_4x4matrix	rotation;

	property = json_value_by_key(json, "rotation");
	if (get_rotation_matrix(property, &rotation))
		return (-1);
	torus->matrix = invert_matrix(rotation);
	property = json_value_by_key(json, "center");
	center = json2vec(property, 1);
	if (!is_valid_vector(center))
		return (-1);
	torus->center = center;
	return (0);
}

int	add_toruss_values(void **primitive, t_json json)
{
	t_torus	torus;

	if (get_torus(json, &torus))
		return (-1);
	if (transform_torus(json, &torus))
		return (-1);
	*primitive = malloc(sizeof(t_torus));
	((t_torus*)(*primitive))[0] = torus;
	return (0);
}
