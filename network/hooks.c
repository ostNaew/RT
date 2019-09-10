/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 18:41:45 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 16:00:52 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

void	on_connect(dyad_Event *e)
{
	(void)e;
	return ;
}

void	release_connection(dyad_Event *e)
{
	free(e->udata);
}

void	on_closed(dyad_Event *e)
{
	(void)e;
	exit(0);
}

void	on_error(dyad_Event *event)
{
	(void)event;
}
