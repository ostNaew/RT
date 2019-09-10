/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_intermediate_result.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 17:55:30 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:57:20 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "engine_render.h"

void	load_intermediate_result(t_render *render)
{
	int	fd;
	int tmp;

	fd = open("intermediate.rt_save", O_RDWR);
	if (fd != -1)
	{
		read(fd, &tmp, sizeof(int));
		if (tmp == render->window_width)
		{
			read(fd, &tmp, sizeof(int));
			if (tmp == render->window_height)
			{
				read(fd, &render->camera, sizeof(t_camera));
				read(fd, render->pixels, sizeof(t_pixel) *
					(size_t)render->window_width *
					(size_t)render->window_height);
			}
		}
		close(fd);
	}
}
