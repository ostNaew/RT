/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_task.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:11:20 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 21:17:16 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

static uint32_t	*last_pixel(void)
{
	static uint32_t	pix_num;

	return (&pix_num);
}

static t_task	*get_task(void)
{
	static t_task	task;

	return (&task);
}

static void		fill_hash(t_task *task)
{
	t_hash	*map_dependent;

	map_dependent = map_dependent_hash();
	task->meta.map_dependent =
		siphash24((void*)task, sizeof(t_task), (char*)map_dependent);
	task->meta.build_dependent =
		siphash24((void*)task, sizeof(t_task), HASH_KEY);
}

static void		fill_samples(t_task *task, t_render *render)
{
	uint32_t	i;
	uint32_t	*current_pix;
	uint32_t	size;
	t_sample	current_sample;

	current_pix = last_pixel();
	current_sample.pixel = (t_pixel){
		.color = (t_vector){0., 0., 0., 0.}, .divider = 0};
	size = (uint32_t)(render->window_width * render->window_height);
	i = -1;
	while (++i < (8192 - sizeof(t_task_meta)) / sizeof(t_sample) - 1)
	{
		current_sample.pix_num = (*current_pix + i) % size;
		task->samples[i] = current_sample;
	}
	*current_pix = (*current_pix + i) % size;
}

void			send_task(dyad_Stream *slave, t_render *render)
{
	t_task	*task;

	task = get_task();
	task->meta.camera = render->camera;
	task->meta.width = render->window_width;
	task->meta.height = render->window_height;
	task->meta.map_dependent = 0;
	task->meta.build_dependent = 0;
	task->meta.spp = 2;
	fill_samples(task, render);
	fill_hash(task);
	dyad_write(slave, (void*)task, sizeof(t_task));
}
