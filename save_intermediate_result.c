/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_intermediate_result.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 17:15:47 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 15:42:25 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "engine_render.h"

void	save_intermediate_result(t_render *render)
{
	int	fd;

	fd = open("intermediate.rt_save", O_TRUNC | O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd != -1)
	{
		write(fd, &render->window_width, sizeof(int));
		write(fd, &render->window_height, sizeof(int));
		write(fd, &render->camera, sizeof(t_camera));
		write(fd, render->pixels, sizeof(t_pixel) *
				(size_t)render->window_width * (size_t)render->window_height);
		close(fd);
		render->last_save_time = SDL_GetTicks();
	}
}
