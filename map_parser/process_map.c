/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:33:01 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/23 16:53:42 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	process_map(t_render *render, t_json json, int load_images)
{
	if (process_camera(render, json_value_by_key(json, "camera")))
		return (-1);
	if (process_images(render, json_value_by_key(json, "images"), load_images))
		return (-1);
	if (process_materials(render, json_value_by_key(json, "materials")))
		return (-1);
	if (process_lights(render, json_value_by_key(json, "lights")))
		return (-1);
	if (process_objects(render, json_value_by_key(json, "objects")))
		return (-1);
	if (process_transformations(render,
			json_value_by_key(json, "transformations")))
		return (-1);
	return (0);
}
