/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_task.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:39:39 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 19:17:16 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_task.h"

static t_ray	get_ray(t_camera camera, int index, int width, int height)
{
	t_4x4matrix	rotation;
	t_vector	point[2];
	t_ray		ray;

	rotation = matrix_mul(
			get_rotation_matrix_x(-camera.polar_angle),
			get_rotation_matrix_z(-camera.azimuthal_angle));
	point[0] = rand_vec_in_hemisphere((t_vector){0., 1., 0., 0.});
	point[0].y = 0.;
	point[0] = vector_scalar_mul(point[0], camera.lens_radius);
	point[1] = vector_sum(vector_matrix_mul(point[0], rotation),
			camera.position);
	point[0] = vector_scalar_mul(point[0], -1);
	ray.direction = normalize(vector_matrix_mul(
		vector_sum((t_vector){-(index % width - width / 2),
			camera.focus, -(index / width - height / 2), 0.}, point[0]),
		rotation));
	ray.origin = point[1];
	return (ray);
}

static int		process_sample(void *data)
{
	SDL_sem			*semaphore;
	t_thread_arg	*arg;
	t_ray			ray;
	size_t			i;

	arg = (t_thread_arg*)data;
	semaphore = arg->semaphore;
	i = -1;
	while (++i < arg->spp)
	{
		ray = get_ray(arg->render->camera, (int)arg->sample->pix_num,
				arg->render->window_width, arg->render->window_height);
		arg->sample->pixel.color = vector_sum(arg->sample->pixel.color,
				trace_path(arg->render, ray, 20));
		arg->sample->pixel.divider += 1;
	}
	free(data);
	SDL_SemPost(semaphore);
	return (0);
}

void			process_task(t_render *render)
{
	SDL_Thread		*thread;
	SDL_sem			*semaphore;
	size_t			i[2];
	t_thread_arg	*arg;

	i[1] = get_num_samples_in_task();
	semaphore = SDL_CreateSemaphore(PROCESSING_THREADS);
	i[0] = -1;
	while (++i[0] < i[1])
	{
		SDL_SemWait(semaphore);
		arg = (t_thread_arg*)malloc(sizeof(t_thread_arg));
		arg->render = render;
		arg->semaphore = semaphore;
		arg->sample = &render->task->samples[i[0]];
		arg->spp = render->task->meta.spp;
		thread = SDL_CreateThread(process_sample, NULL, (void*)arg);
		SDL_DetachThread(thread);
	}
	while (SDL_SemValue(semaphore) < PROCESSING_THREADS)
		;
	render->working = 0;
	SDL_DestroySemaphore(semaphore);
}
