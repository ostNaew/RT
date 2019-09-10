/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:53:21 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 16:03:02 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network_api.h"

static void	on_accept(dyad_Event *e)
{
	t_connection	*connection;

	connection = (t_connection*)ft_memalloc(sizeof(t_connection));
	connection->render = (t_render*)e->udata;
	dyad_addListener(e->remote, DYAD_EVENT_DATA, data_hook, (void*)connection);
	dyad_addListener(e->remote, DYAD_EVENT_DESTROY, release_connection, NULL);
}

static void	init_master(t_render *render, int port)
{
	render->mode = MASTER;
	render->stream = dyad_newStream();
	dyad_addListener(render->stream, DYAD_EVENT_ACCEPT, on_accept,
			(void*)render);
	dyad_listen(render->stream, port == 0 ? 8000 : port);
}

static void	init_slave(t_render *render, const char *host, int port)
{
	t_connection	*connection;

	connection = get_connection();
	connection->render = render;
	render->mode = SLAVE;
	render->stream = dyad_newStream();
	dyad_connect(render->stream, host, port == 0 ? 8000 : port);
	dyad_addListener(render->stream, DYAD_EVENT_DATA, data_hook,
			(void*)connection);
	dyad_addListener(render->stream, DYAD_STATE_CLOSED, on_closed, NULL);
}

void		init_network(t_render *render, const char *host, int port)
{
	t_hash	*hash;
	size_t	i;

	i = -1;
	hash = map_dependent_hash();
	hash[0] = 0;
	dyad_init();
	if (host)
		init_slave(render, host, port);
	else
		init_master(render, port);
	while (++i < render->n_images)
	{
		hash[1] = siphash24((void*)render->images[i].image_data,
			sizeof(int32_t) * render->images[i].width *
			render->images[i].height, HASH_KEY);
		hash[0] = siphash24((void*)hash, sizeof(*hash) * 2, HASH_KEY);
	}
	hash[1] = siphash24((void*)render->map_str, ft_strlen(render->map_str),
			HASH_KEY);
	dyad_addListener(render->stream, DYAD_EVENT_CONNECT, on_connect, NULL);
	dyad_addListener(render->stream, DYAD_EVENT_ERROR, on_error, NULL);
}
