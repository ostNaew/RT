/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:58:27 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/28 19:39:30 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

int	camera_rotation_key_hook(SDL_Event *event, t_render *render)
{
	if (event->key.keysym.sym == SDLK_LEFT && (render->render_needed = 1)
			&& !render->path_tracing)
		render->camera.azimuthal_angle -= 0.0523599;
	else if (event->key.keysym.sym == SDLK_RIGHT && (render->render_needed = 1)
			&& !render->path_tracing)
		render->camera.azimuthal_angle += 0.0523599;
	else if (event->key.keysym.sym == SDLK_UP && (render->render_needed = 1)
			&& !render->path_tracing)
		render->camera.polar_angle += 0.0523599;
	else if (event->key.keysym.sym == SDLK_DOWN && (render->render_needed = 1)
			&& !render->path_tracing)
		render->camera.polar_angle -= 0.0523599;
	else if (event->key.keysym.sym == SDLK_p && (render->render_needed = 1))
		render->path_tracing = !render->path_tracing;
	else
		return (0);
	return (1);
}

int	movement_key_hook(SDL_Event *e, t_render *render)
{
	t_vector	v_front;

	v_front = normalize(vector_matrix_mul((t_vector){0., 1., 0., 0.},
			get_rotation_matrix_z(-render->camera.azimuthal_angle)));
	if ((e->key.keysym.sym == SDLK_SPACE ||
			e->key.keysym.sym == SDLK_TAB) && (render->render_needed = 1) &&
			!render->path_tracing)
		render->camera.position.z += (e->key.keysym.sym == SDLK_TAB) ? -1 : 1;
	else if (e->key.keysym.sym == SDLK_w && (render->render_needed = 1) &&
			!render->path_tracing)
		render->camera.position = vector_sum(render->camera.position, v_front);
	else if (e->key.keysym.sym == SDLK_s && (render->render_needed = 1) &&
			!render->path_tracing)
		render->camera.position = vector_sub(render->camera.position, v_front);
	else if (e->key.keysym.sym == SDLK_d && (render->render_needed = 1) &&
			!render->path_tracing)
		render->camera.position = vector_sum(render->camera.position,
				normalize(cross((t_vector){0, 0, 1, 0}, v_front)));
	else if (e->key.keysym.sym == SDLK_a && (render->render_needed = 1) &&
			!render->path_tracing)
		render->camera.position = vector_sub(render->camera.position,
				normalize(cross((t_vector){0, 0, 1, 0}, v_front)));
	else
		return (0);
	return (1);
}

int	filters_key_hook(SDL_Event *event, t_render *render)
{
	if (event->key.keysym.sym == SDLK_1 && (render->render_needed = 1))
		active_filter(1, 0);
	else if (event->key.keysym.sym == SDLK_2 && (render->render_needed = 1))
		active_filter(2, 0);
	else if (event->key.keysym.sym == SDLK_3 && (render->render_needed = 1))
		active_filter(3, 0);
	else if (event->key.keysym.sym == SDLK_4 && (render->render_needed = 1))
		active_filter(4, 0);
	else if (event->key.keysym.sym == SDLK_5 && (render->render_needed = 1))
		active_filter(5, 0);
	else if (event->key.keysym.sym == SDLK_EQUALS &&
			(render->render_needed = 1))
		active_filter(0, 2);
	else if (event->key.keysym.sym == SDLK_MINUS &&
			(render->render_needed = 1))
		active_filter(0, -2);
	else if (event->key.keysym.sym == SDLK_PAGEUP &&
			(render->render_needed = 1))
		get_index_brightness(1.2);
	else if (event->key.keysym.sym == SDLK_PAGEDOWN &&
			(render->render_needed = 1))
		get_index_brightness(0.8);
	else
		return (0);
	return (1);
}
