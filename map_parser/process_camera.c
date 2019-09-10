/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 21:23:33 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/09 14:19:36 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

static int	add_value(t_json json, double *value, double default_value,
	int flag)
{
	if (json.type == JSON_NULL)
	{
		*value = default_value;
		return (0);
	}
	else if (json.type != JSON_NUMBER)
		return (-1);
	if (flag)
		if (json.value.number < 0)
			return (-1);
	if (flag != 2)
		*value = (double)json.value.number * M_PI / 180.;
	else
		*value = (double)json.value.number;
	return (0);
}

int			process_camera(t_render *render, t_json json)
{
	t_json		property;
	t_vector	position;

	if (json.type != JSON_OBJECT)
		return (-1);
	property = json_value_by_key(json, "position");
	position = json2vec(property, 1);
	if (!is_valid_vector(position))
		return (-1);
	render->camera.position = position;
	property = json_value_by_key(json, "lens_radius");
	if (add_value(property, &render->camera.lens_radius, 0., 2))
		return (-1);
	property = json_value_by_key(json, "polar_angle");
	if (add_value(property, &render->camera.polar_angle, 0., 0))
		return (-1);
	property = json_value_by_key(json, "azimuthal_angle");
	if (add_value(property, &render->camera.azimuthal_angle, 0., 0))
		return (-1);
	property = json_value_by_key(json, "view_angle");
	if (add_value(property, &render->camera.view_angle, 60. * M_PI / 180., 1))
		return (-1);
	return (0);
}
