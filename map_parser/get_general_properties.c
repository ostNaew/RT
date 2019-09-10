/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_general_properties.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:24:36 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/24 18:39:51 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	add_type(t_primitive_type *type, char *str)
{
	if (ft_strequ(str, "plane"))
		*type = PLANE;
	else if (ft_strequ(str, "sphere"))
		*type = SPHERE;
	else if (ft_strequ(str, "cylinder"))
		*type = CYLINDER;
	else if (ft_strequ(str, "triangle"))
		*type = TRIANGLE;
	else if (ft_strequ(str, "cone"))
		*type = CONE;
	else if (ft_strequ(str, "circle"))
		*type = CIRCLE;
	else if (ft_strequ(str, "paraboloid"))
		*type = PARABOLOID;
	else if (ft_strequ(str, "torus"))
		*type = TORUS;
	else
		return (-1);
	return (0);
}

int	add_material(t_render *render, t_material **material, t_json json)
{
	size_t	index_material;

	if (json.type != JSON_NUMBER && json.type != JSON_NULL)
		return (-1);
	if (json.type == JSON_NUMBER && json.value.number < 0.)
		return (-1);
	index_material = (json.type == JSON_NULL ?
			0 : (size_t)json.value.number + 1);
	if (index_material >= render->n_materials)
		return (-1);
	*material = &render->materials[index_material];
	return (0);
}

int	add_texture(t_render *render, t_texture *texture, t_json json)
{
	t_json	property;
	size_t	i;

	if (json.type != JSON_OBJECT && json.type != JSON_NULL)
		return (-1);
	if (json.type == JSON_NULL)
	{
		texture->image = NULL;
		return (0);
	}
	property = json_value_by_key(json, "index");
	i = -1;
	i = property.type == JSON_NUMBER ? (size_t)property.value.number : i;
	if (property.type != JSON_NUMBER || i >= render->n_images)
		return (-1);
	texture->image = &render->images[i];
	property = json_value_by_key(json, "inv_hor");
	if (property.type != JSON_BOOL)
		return (-1);
	texture->inv_hor = (char)property.value.boolean;
	property = json_value_by_key(json, "inv_vert");
	if (property.type != JSON_BOOL)
		return (-1);
	texture->inv_vert = (char)property.value.boolean;
	return (0);
}

int	add_color(int *color, t_json json)
{
	if (json.type != JSON_STRING && json.type != JSON_NULL)
		return (-1);
	if (json.type == JSON_NULL)
	{
		*color = 0xc0c0c0;
		return (0);
	}
	*color = atoi_hex(json.value.string);
	if (*color & 0xff000000)
		return (-1);
	return (0);
}
