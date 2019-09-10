/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:04:32 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/08 21:01:03 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

static int	add_value(t_json json, double *value, double min_value, int flag)
{
	if (json.type != JSON_NUMBER)
		return (-1);
	if (json.value.number < min_value)
		return (-1);
	if (flag)
		*value = (double)json.value.number * M_PI / 180.;
	else
		*value = (double)json.value.number;
	return (0);
}

static int	add_type_light(t_light_type *type, char *str)
{
	if (ft_strequ(str, "ambient"))
		*type = AMBIENT;
	else if (ft_strequ(str, "point"))
		*type = POINT;
	else if (ft_strequ(str, "directional"))
		*type = DIRECTIONAL;
	else if (ft_strequ(str, "parallel"))
		*type = PARALLEL;
	else
		return (-1);
	return (0);
}

static int	add_vector(t_json json, t_vector *vector, char *key)
{
	json = json_value_by_key(json, key);
	*vector = json2vec(json, ft_strequ(key, "position"));
	if (!is_valid_vector(*vector))
		return (-1);
	return (0);
}

static int	get_values_light(t_render *render, t_json json, size_t index)
{
	t_json	property;

	property = json_value_by_key(json, "type");
	if (property.type != JSON_STRING)
		return (-1);
	if (add_type_light(&render->lights[index].type, property.value.string))
		return (-1);
	property = json_value_by_key(json, "intensity");
	if (add_value(property, &render->lights[index].intensity, 0, 0))
		return (-1);
	if (render->lights[index].type == POINT ||
			render->lights[index].type == DIRECTIONAL)
		if (add_vector(json, &render->lights[index].position, "position"))
			return (-1);
	if (render->lights[index].type == PARALLEL ||
			render->lights[index].type == DIRECTIONAL)
		if (add_vector(json, &render->lights[index].direction, "direction"))
			return (-1);
	if (render->lights[index].type == DIRECTIONAL)
	{
		property = json_value_by_key(json, "angle");
		if (add_value(property, &render->lights[index].angle, 0, 1))
			return (-1);
	}
	return (0);
}

int			process_lights(t_render *render, t_json json)
{
	t_json		element;
	size_t		i;

	if (json.type != JSON_ARRAY && json.type != JSON_NULL)
		return (-1);
	render->n_lights = json.size;
	if (json.type == JSON_NULL)
		return (0);
	render->lights = malloc(sizeof(t_lightsource) * json.size);
	if (render->lights == NULL)
		return (-1);
	i = -1;
	while (++i < json.size)
	{
		element = json_value_by_index(json, i);
		if (element.type != JSON_OBJECT ||
				get_values_light(render, element, i))
			return (-1);
	}
	return (0);
}
