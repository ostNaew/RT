/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_data_hook.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:29:03 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 15:32:18 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

void			master_data_hook(dyad_Event *event)
{
	t_render		*render;

	render = ((t_connection*)event->udata)->render;
	if ((unsigned long)event->size >=
		sizeof("get_task") - 1 + sizeof(t_nonce) + sizeof(t_hash) * 2 &&
			ft_strnequ(event->data, "get_task", sizeof("get_task") - 1) &&
			check_validity_msg(event) == 0)
		send_task(event->stream, render);
	else if (event->size == sizeof(t_task) && check_validity_task(event) == 0)
		receive_result(event);
}
