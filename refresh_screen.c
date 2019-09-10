/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:23:04 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 20:40:51 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

void		set_pixel(SDL_Surface *surface, int x, int y, int pixel)
{
	int *target_pixel;

	target_pixel = (int*)(surface->pixels +
			y * surface->pitch + x * sizeof(*target_pixel));
	*target_pixel = pixel;
}

static void	refresh_screen(t_render *render)
{
	t_vector	color;
	int			i;

	i = -1;
	SDL_SetWindowResizable(render->window, SDL_FALSE);
	render->image = SDL_GetWindowSurface(render->window);
	while (++i < render->window_width * render->window_height)
	{
		color = apply_filters(render, i);
		set_pixel(render->image,
			i % render->window_width,
			i / render->window_width,
			vec2color(color));
	}
	SDL_UpdateWindowSurface(render->window);
	SDL_SetWindowResizable(render->window, SDL_TRUE);
}

int			refresh_thread(void *data)
{
	t_render	*render;
	uint32_t	ticks;

	render = (t_render*)data;
	ticks = 0;
	while (1)
		if (render->refresh_needed && SDL_TICKS_PASSED(SDL_GetTicks(), ticks))
		{
			refresh_screen(render);
			ticks = SDL_GetTicks() + 1000;
			render->refresh_needed = 0;
		}
}
