/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 17:32:07 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 15:27:51 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

static void	window_hook(SDL_Event *event, t_render *render)
{
	if (event->window.event == SDL_WINDOWEVENT_RESIZED)
	{
		SDL_SetWindowResizable(render->window, SDL_FALSE);
		render->window_width = event->window.data1;
		render->window_height = event->window.data2;
		render->image = SDL_GetWindowSurface(render->window);
		render->camera.focus = (render->window_width / 2) /
			tan((render->camera.view_angle / 2.));
		render->render_needed = 1;
		clear_pixels_buffer(render);
	}
}

static void	key_hook(SDL_Event *event, t_render *render)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		exit(0);
	else if (camera_rotation_key_hook(event, render))
		return ;
	else if (movement_key_hook(event, render))
		return ;
	else if (filters_key_hook(event, render))
		return ;
	else if (event->key.keysym.sym == SDLK_i)
		save_intermediate_result(render);
	else if (event->key.keysym.sym == SDLK_l)
		load_intermediate_result(render);
	else if (event->key.keysym.sym == SDLK_k &&
			(render->autosave = !render->autosave))
		save_intermediate_result(render);
}

void		main_loop(t_render *render)
{
	SDL_Event	event;

	while (1)
	{
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				exit(0);
			else if (event.type == SDL_WINDOWEVENT)
				window_hook(&event, render);
			else if (event.type == SDL_KEYDOWN)
				key_hook(&event, render);
		if (render->autosave && SDL_TICKS_PASSED(SDL_GetTicks(),
				render->last_save_time + 10 * 60 * 1000))
			save_intermediate_result(render);
		if (render->mode == MASTER)
			networking(render);
	}
}

void		slave_main_loop(t_render *render)
{
	while (1)
	{
		if (render->working)
			process_task(render);
		else if (render->task)
			send_result(render);
		else
			networking(render);
	}
}
