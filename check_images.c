/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_images.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 19:01:28 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/21 21:04:03 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"

int	check_images(t_render *render)
{
	size_t	i;

	i = -1;
	while (++i < render->n_images && render->images)
		if (render->images[i].image_data == NULL)
			return ((int)i);
	return (-1);
}
