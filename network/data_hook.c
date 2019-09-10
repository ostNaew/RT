/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:32:38 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 15:31:25 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

void	data_hook(dyad_Event *event)
{
	if (!(event && event->data))
		return ;
	if (((t_connection*)event->udata)->render->mode == MASTER)
		master_data_hook(event);
	else if (((t_connection*)event->udata)->render->mode == SLAVE)
		slave_data_hook(event);
}
