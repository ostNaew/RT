/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_materials.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:21:46 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/24 13:26:51 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

static void	get_default_material(t_render *render, size_t index)
{
	render->materials[index].light_intensity = 0.;
	render->materials[index].emittance = 0.;
	render->materials[index].albedo = 1.;
	render->materials[index].specular = 0.;
	render->materials[index].specular_exponent = 0;
	render->materials[index].refraction = 0.;
	render->materials[index].refractive_index = 1.;
}

static int	add_value(t_json json, double *value, double min_value)
{
	if (json.type == JSON_NULL)
		return (0);
	if (json.type != JSON_NUMBER)
		return (-1);
	if (json.value.number < min_value)
		return (-1);
	*value = (double)json.value.number;
	return (0);
}

static int	get_values_material(t_render *render, t_json json, size_t index)
{
	t_json	property;

	get_default_material(render, index);
	property = json_value_by_key(json, "light_intensity");
	if (add_value(property, &render->materials[index].light_intensity, 0))
		return (-1);
	property = json_value_by_key(json, "albedo");
	if (add_value(property, &render->materials[index].albedo, 0))
		return (-1);
	property = json_value_by_key(json, "specular");
	if (add_value(property, &render->materials[index].specular, 0))
		return (-1);
	property = json_value_by_key(json, "specular_exponent");
	if (add_value(property, &render->materials[index].specular_exponent, 0))
		return (-1);
	property = json_value_by_key(json, "refraction");
	if (add_value(property, &render->materials[index].refraction, 0))
		return (-1);
	property = json_value_by_key(json, "refractive_index");
	if (add_value(property, &render->materials[index].refractive_index, 1))
		return (-1);
	property = json_value_by_key(json, "emittance");
	if (add_value(property, &render->materials[index].emittance, 0))
		return (-1);
	return (0);
}

int			process_materials(t_render *render, t_json json)
{
	t_json		element;
	size_t		i;

	if (json.type != JSON_ARRAY && json.type != JSON_NULL)
		return (-1);
	render->materials = malloc(sizeof(t_material) * (json.size + 1));
	render->n_materials = json.size + 1;
	if (render->materials == NULL)
		return (-1);
	get_default_material(render, 0);
	i = 0;
	while (++i <= json.size)
	{
		element = json_value_by_index(json, i - 1);
		if (element.type != JSON_OBJECT ||
				get_values_material(render, element, i))
			return (-1);
		render->materials[i] = normalize_material(render->materials[i]);
	}
	return (0);
}
