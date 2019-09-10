/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:49:42 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/24 18:39:52 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	add_value_to_primitive(void **primitive, t_primitive_type type, t_json json)
{
	if (type == PLANE || type == TRIANGLE || type == CIRCLE)
		if (add_planes_values(primitive, type, json))
			return (-1);
	if (type == SPHERE)
		if (add_spheres_values(primitive, json))
			return (-1);
	if (type == CYLINDER)
		if (add_cylinders_values(primitive, json))
			return (-1);
	if (type == CONE)
		if (add_cones_values(primitive, json))
			return (-1);
	if (type == PARABOLOID)
		if (add_paraboloids_values(primitive, json))
			return (-1);
	if (type == TORUS)
		if (add_toruss_values(primitive, json))
			return (-1);
	return (0);
}

int	process_primitive(t_render *render, t_primitive *primitive, t_json json)
{
	t_json	property;

	property = json_value_by_key(json, "type");
	if (property.type != JSON_STRING ||
			add_type(&primitive->type, property.value.string))
		return (-1);
	property = json_value_by_key(json, "material");
	if (add_material(render, &primitive->material, property))
		return (-1);
	property = json_value_by_key(json, "normal_map");
	if (add_texture(render, &primitive->normal_map, property))
		return (-1);
	property = json_value_by_key(json, "texture");
	if (add_texture(render, &primitive->texture, property))
		return (-1);
	if (property.type == JSON_NULL)
		if (add_color(&primitive->texture.color,
				json_value_by_key(json, "color")))
			return (-1);
	if (add_value_to_primitive(&primitive->primitive, primitive->type, json))
		return (-1);
	return (0);
}

int	process_object(t_render *render, t_json json_object, size_t i)
{
	t_json	json_primitives;
	t_json	json_primitive;
	size_t	j;

	if (json_object.type != JSON_OBJECT)
		return (-1);
	if (add_boundary(&render->scene.objects[i], json_object))
		return (-1);
	render->scene.objects[i].bounded = 0;
	json_primitives = json_value_by_key(json_object, "primitives");
	if (json_primitives.type != JSON_ARRAY)
		return (-1);
	render->scene.objects[i].n_primitives = json_primitives.size;
	if (!(render->scene.objects[i].primitives = malloc(sizeof(t_primitive) *
					json_primitives.size)))
		return (-1);
	j = -1;
	while (++j < json_primitives.size)
	{
		json_primitive = json_value_by_index(json_primitives, j);
		if (json_primitive.type != JSON_OBJECT || process_primitive(render,
					&render->scene.objects[i].primitives[j], json_primitive))
			return (-1);
	}
	return (0);
}

int	process_objects(t_render *render, t_json json)
{
	size_t	i;
	t_json	json_object;

	if (json.type != JSON_ARRAY)
		return (-1);
	render->scene.n_objects = json.size;
	render->scene.objects = malloc(sizeof(t_object) * render->scene.n_objects);
	if (render->scene.objects == NULL)
		return (-1);
	i = -1;
	while (++i < render->scene.n_objects)
	{
		json_object = json_value_by_index(json, i);
		if (process_object(render, json_object, i))
			return (-1);
	}
	return (0);
}
