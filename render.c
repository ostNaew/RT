/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:16:01 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 15:33:44 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

static void	render_window(t_render *render)
{
	static int	pt;

	if (render->path_tracing != pt)
	{
		pt = render->path_tracing;
		clear_pixels_buffer(render);
	}
	if (render->path_tracing)
		path_tracing(render);
	else
	{
		clear_pixels_buffer(render);
		ray_tracing(render);
		render->render_needed = 0;
	}
	render->refresh_needed = 1;
}

int			render_thread(void *data)
{
	t_render	*render;
	uint32_t	ticks;

	ticks = 0;
	render = (t_render*)data;
	while (1)
		if (render->render_needed && SDL_TICKS_PASSED(SDL_GetTicks(), ticks))
		{
			render_window(render);
			ticks = SDL_GetTicks() + 50;
		}
}
