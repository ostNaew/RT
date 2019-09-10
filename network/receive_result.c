/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:53:10 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 16:01:42 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

static void	accumulate_sample(t_sample sample, t_render *render)
{
	render->pixels[sample.pix_num].color =
		vector_sum(render->pixels[sample.pix_num].color, sample.pixel.color);
	render->pixels[sample.pix_num].divider += sample.pixel.divider;
}

static void	accumulate_result(t_task *task, t_render *render)
{
	size_t	i;

	i = -1;
	while (++i < (8192 - sizeof(t_task_meta)) / sizeof(t_sample) - 1)
		accumulate_sample(task->samples[i], render);
}

void		receive_result(dyad_Event *event)
{
	t_render	*render;
	t_task		*task;

	task = (t_task*)event->data;
	render = ((t_connection*)event->udata)->render;
	if (ft_memcmp((void*)&task->meta.camera, (void*)&render->camera,
				sizeof(t_camera)))
		return ;
	if (task->meta.width != render->window_width ||
			task->meta.height != render->window_height)
		return ;
	render = ((t_connection*)event->udata)->render;
	accumulate_result(task, render);
	render->refresh_needed = 1;
}
