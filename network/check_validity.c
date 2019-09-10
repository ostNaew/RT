/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:27:50 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 15:29:21 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

int	check_validity_task(dyad_Event *event)
{
	t_task	*task;
	t_hash	map;
	t_hash	build;
	t_hash	hash;

	task = (t_task*)event->data;
	map = task->meta.map_dependent;
	build = task->meta.build_dependent;
	task->meta.map_dependent = 0;
	task->meta.build_dependent = 0;
	hash = siphash24((void*)task, sizeof(t_task), (char*)map_dependent_hash());
	if (hash != map)
		return (-1);
	task->meta.map_dependent = map;
	hash = siphash24((void*)task, sizeof(t_task), HASH_KEY);
	if (hash != build)
		return (-2);
	return (0);
}

int	check_validity_msg(dyad_Event *event)
{
	t_hash	hash;
	t_hash	*map_dependent;

	hash = *((t_hash*)(event->data + sizeof("get_task") - 1 + sizeof(t_nonce)));
	map_dependent = map_dependent_hash();
	if (hash != siphash24((void*)event->data,
				sizeof("get_task") - 1 + sizeof(t_nonce), (char*)map_dependent))
		return (-1);
	hash = *((t_hash*)(event->data + sizeof("get_task") - 1 + sizeof(t_nonce) +
				sizeof(t_hash)));
	if (hash != siphash24((void*)event->data, event->size - sizeof(t_hash),
				HASH_KEY))
		return (-2);
	return (0);
}
