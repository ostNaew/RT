/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   networking.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 18:13:26 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 20:54:55 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "network_api.h"

int		its_time(uint32_t delay)
{
	static uint32_t	last_request;
	uint32_t		current_time;

	current_time = SDL_GetTicks() - last_request;
	if (SDL_TICKS_PASSED(current_time, delay))
	{
		last_request = SDL_GetTicks();
		return (1);
	}
	return (0);
}

void	networking(t_render *render)
{
	dyad_update();
	if (render->mode != SLAVE)
		return ;
	else if (!render->working && its_time(100))
		request_task(render->stream);
}
