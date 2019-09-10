/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_api.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 18:34:57 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 19:50:33 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_API_H
# define NETWORK_API_H

# ifndef HASH_KEY
#  define HASH_KEY "TtAu6WXqqMS4LM0p"
# endif

# include <stdint.h>
# include "engine_render.h"
# include "dyad.h"

typedef uint64_t	t_nonce;

typedef struct	s_sample
{
	t_pixel		pixel;
	uint32_t	pix_num;
}				t_sample;

typedef struct	s_task_meta
{
	t_camera	camera;
	int32_t		width;
	int32_t		height;
	size_t		spp;
	t_nonce		nonce;
	t_hash		map_dependent;
	t_hash		build_dependent;
}				t_task_meta;

typedef struct	s_task
{
	t_sample	samples[(8192 - sizeof(t_task_meta)) / sizeof(t_sample) - 1];
	t_task_meta	meta;
}				t_task;

typedef struct	s_connection
{
	t_nonce		nonce;
	t_render	*render;
}				t_connection;

void			data_hook(dyad_Event *event);
void			on_error(dyad_Event *event);
void			on_closed(dyad_Event *e);
void			on_connect(dyad_Event *e);
void			release_connection(dyad_Event *e);

/*
**	DATA
**------------------------------------------------------------------------------
**	data_singleton.c
**------------------------------------------------------------------------------
*/

int				check_validity_task(dyad_Event *event);
int				check_validity_msg(dyad_Event *event);

/*
**	DATA
**------------------------------------------------------------------------------
**	data_singleton.c
**------------------------------------------------------------------------------
*/

t_hash			*map_dependent_hash(void);
t_connection	*get_connection(void);

/*
**	MASTER_FUNCTIONS
*/

void			master_data_hook(dyad_Event *event);
void			receive_result(dyad_Event *event);
void			send_task(dyad_Stream *slave, t_render *render);

/*
**	SLAVE_FUNCTIONS
*/

void			slave_data_hook(dyad_Event *event);
t_nonce			get_nonce(void);
void			receive_task(dyad_Event *event);
void			request_task(dyad_Stream *master);
void			send_result(t_render *render);

#endif
