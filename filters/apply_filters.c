/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_filters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:32:56 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/24 13:15:33 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filters.h"

static t_vector	color_from_image(t_render *render, int x, int y)
{
	size_t	i;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= render->window_width)
		x = render->window_width - 1;
	if (y >= render->window_height)
		y = render->window_height - 1;
	i = render->window_width * y + x;
	return (get_color_from_pixel(render->pixels[i]));
}

static t_vector	*get_colors(t_render *render, size_t size, size_t index)
{
	t_vector		*colors;
	size_t			i;
	static size_t	static_size;
	static t_vector	*static_colors;

	if (static_size != size)
	{
		colors = static_colors;
		free(colors);
		static_colors = ft_memalloc(sizeof(t_vector) * size * size);
		static_size = size;
	}
	i = -1;
	while (++i < size * size)
		static_colors[i] = color_from_image(render,
					index % render->window_width - ((int)size / 2) + i % size,
					index / render->window_width - ((int)size / 2) + i / size);
	return (static_colors);
}

t_vector		apply_filters(t_render *render, size_t index)
{
	t_filter	filter;
	t_vector	*colors;
	t_vector	res;

	filter = active_filter(0, 0);
	res = get_color_from_pixel(render->pixels[index]);
	res = vector_scalar_mul(res, get_index_brightness(1.));
	if (filter.filter != NULL)
	{
		colors = get_colors(render, filter.size, index);
		res = filter.filter(colors, filter.size);
	}
	return (res);
}
