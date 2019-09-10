/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_task.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:37:48 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 16:01:59 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

static t_task	*current_task(void)
{
	static t_task	task;

	return (&task);
}

void			receive_task(dyad_Event *event)
{
	t_task		*task;
	t_render	*render;

	task = current_task();
	render = ((t_connection*)event->udata)->render;
	ft_memcpy((void*)task, (void*)event->data, sizeof(t_task));
	render->camera = task->meta.camera;
	render->window_width = task->meta.width;
	render->window_height = task->meta.height;
	render->working = 1;
	render->task = task;
}
