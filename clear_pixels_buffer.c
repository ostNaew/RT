/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_pixels_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:25:25 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/17 18:27:50 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

void	clear_pixels_buffer(t_render *render)
{
	int			i;
	t_vector	empty_pixel;

	i = -1;
	empty_pixel = (t_vector){0., 0., 0., 0.};
	while (++i < render->window_height * render->window_width)
	{
		render->pixels[i].color = empty_pixel;
		render->pixels[i].divider = 0;
	}
}
