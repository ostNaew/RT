/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 19:13:34 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/08 15:25:08 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

void	destroy_objects(t_object **objects, size_t n_objects)
{
	t_object	*tmp;
	size_t		i;
	size_t		j;

	i = -1;
	tmp = *objects;
	while (tmp && ++i < n_objects && (j = -1))
	{
		while (++j < tmp[i].n_primitives)
			free(tmp[i].primitives[j].primitive);
		free(tmp[i].primitives);
	}
	ft_memdel((void**)objects);
}

void	destroy_images(t_netpbm_image **images, size_t n_images)
{
	t_netpbm_image	*tmp;
	size_t			i;

	i = -1;
	tmp = *images;
	while (tmp && ++i < n_images)
		free(tmp[i].image_data);
	ft_memdel((void**)images);
}

void	destroy_map(t_render *render)
{
	ft_memdel((void**)&render->materials);
	ft_memdel((void**)&render->lights);
	destroy_objects(&render->scene.objects, render->scene.n_objects);
	destroy_images(&render->images, render->n_images);
}
