/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_task.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:59:32 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/27 17:53:47 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_TASK_H
# define PROCESS_TASK_H

# include "engine_render.h"
# include "network_api.h"

typedef struct	s_thread_arg
{
	SDL_sem		*semaphore;
	t_render	*render;
	t_sample	*sample;
	size_t		spp;
}				t_thread_arg;

#endif
