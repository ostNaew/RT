/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:22:29 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/27 18:16:36 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int		add_image(t_netpbm_image *image, t_json json, char *location)
{
	int		status;
	char	*name_file;
	char	*tmp;

	if (json.type != JSON_STRING)
		return (-1);
	name_file = ft_strjoin(location, "/images/");
	tmp = name_file;
	name_file = ft_strjoin(name_file, json.value.string);
	free(tmp);
	*image = read_image(name_file, &status);
	free(name_file);
	if (status)
		return (-1);
	return (0);
}

int		process_images(t_render *render, t_json json, int load_images)
{
	size_t	i;

	if (json.type != JSON_ARRAY && json.type != JSON_NULL)
		return (-1);
	render->n_images = json.size;
	render->images = NULL;
	if (json.type == JSON_NULL)
		return (0);
	if (!(render->images =
			(t_netpbm_image*)ft_memalloc(sizeof(t_netpbm_image) * json.size)))
		return (-1);
	i = -1;
	if (load_images)
		while (++i < json.size)
			if (add_image(&render->images[i], json_value_by_index(json, i),
					render->location))
				return (-1);
	return (0);
}
