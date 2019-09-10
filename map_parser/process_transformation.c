/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_transformation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 16:41:03 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/13 15:50:38 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	process_translation(t_render *render, t_json json)
{
	t_json		property;
	size_t		object_index;
	t_vector	vector;

	property = json_value_by_key(json, "object_index");
	if (property.type != JSON_NUMBER)
		return (-1);
	object_index = (size_t)property.value.number;
	if (object_index >= render->scene.n_objects)
		return (-1);
	property = json_value_by_key(json, "vector");
	vector = json2vec(property, 0);
	if (!is_valid_vector(vector))
		return (-1);
	process_translation_primitives(render, object_index, vector);
	return (0);
}

int	process_rotation(t_render *render, t_json json)
{
	t_json		property;
	size_t		object_index;
	t_4x4matrix	rotation;

	property = json_value_by_key(json, "object_index");
	if (property.type != JSON_NUMBER || property.value.number < 0 ||
			property.value.number >= render->scene.n_objects)
		return (-1);
	object_index = (size_t)property.value.number;
	property = json_value_by_key(json, "rotation");
	if (get_rotation_matrix(property, &rotation))
		return (-1);
	process_rotation_primitives(render, object_index, rotation);
	return (0);
}

int	process_transformations(t_render *render, t_json json)
{
	size_t	i;
	t_json	element;
	t_json	property;

	if (json.type != JSON_ARRAY && json.type != JSON_NULL)
		return (-1);
	if (json.type == JSON_NULL)
		return (0);
	i = -1;
	while (++i < json.size)
	{
		element = json_value_by_index(json, i);
		if (element.type != JSON_OBJECT)
			return (-1);
		property = json_value_by_key(element, "type");
		if (property.type != JSON_STRING)
			return (-1);
		if (ft_strequ(property.value.string, "translation"))
			if (process_translation(render, element))
				return (-1);
		if (ft_strequ(property.value.string, "rotation"))
			if (process_rotation(render, element))
				return (-1);
	}
	return (0);
}
