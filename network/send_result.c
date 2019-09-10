/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_result.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:01:00 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 16:02:13 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

static void		fill_hash(t_task *task)
{
	t_hash	*map_dependent;

	task->meta.map_dependent = 0;
	task->meta.build_dependent = 0;
	map_dependent = map_dependent_hash();
	task->meta.map_dependent =
		siphash24((void*)task, sizeof(t_task), (char*)map_dependent);
	task->meta.build_dependent =
		siphash24((void*)task, sizeof(t_task), HASH_KEY);
}

void			send_result(t_render *render)
{
	fill_hash(render->task);
	dyad_write(render->stream, (void*)render->task, sizeof(t_task));
	render->working = 0;
	render->task = NULL;
}
