/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:17:03 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 20:38:09 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

static void	ft_assert(int condition)
{
	if (condition == 0)
	{
		write(1, "error\n", sizeof("error\n") - 1);
		exit(0);
	}
}

void		init_sdl(t_render *render)
{
	render->window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	ft_assert(render->window != NULL);
	render->image = SDL_GetWindowSurface(render->window);
	render->camera.focus = (render->window_width / 2) /
		tan((render->camera.view_angle / 2.));
	render->render_needed = 1;
}

int			main(int argc, char **argv)
{
	t_render	*render;
	size_t		full_size;
	SDL_Thread	*thread;

	srand(time(NULL));
	ft_assert(SDL_Init(SDL_INIT_EVERYTHING) == 0);
	full_size = WINDOW_FULLSCREEN_WIDTH * WINDOW_FULLSCREEN_HEIGHT;
	render = malloc(sizeof(t_render));
	ft_assert((render->rays = malloc(sizeof(t_ray) * full_size)) != NULL);
	ft_assert((render->pixels = malloc(sizeof(t_pixel) * full_size)) != NULL);
	ft_assert(init(render, argc, argv) == 0);
	if (render->mode == SLAVE)
		slave_main_loop(render);
	else
	{
		init_sdl(render);
		thread = SDL_CreateThread(render_thread, NULL, (void*)render);
		SDL_DetachThread(thread);
		thread = SDL_CreateThread(refresh_thread, NULL, (void*)render);
		SDL_DetachThread(thread);
		main_loop(render);
	}
	return (0);
}
