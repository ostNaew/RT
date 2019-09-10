/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slave_data_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:15:20 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 19:03:46 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

void	slave_data_hook(dyad_Event *event)
{
	if (event->size == sizeof(t_task) && check_validity_task(event) == 0)
		receive_task(event);
}
