/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 17:51:51 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/08 17:34:27 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

int	get_color_uv(t_texture texture, t_uv uv)
{
	size_t		i;
	size_t		j;

	if (texture.image == NULL)
	{
		return (texture.color);
	}
	i = ((texture.inv_vert ? 1. - uv.v : uv.v) * texture.image->height);
	j = ((texture.inv_hor ? 1. - uv.u : uv.u) * texture.image->width);
	if (i > texture.image->height)
		i = texture.image->height;
	if (j > texture.image->width)
		j = texture.image->width;
	return (texture.image->image_data[i * texture.image->width + j]);
}
