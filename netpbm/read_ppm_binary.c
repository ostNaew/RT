/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ppm_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 14:03:50 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/13 16:17:06 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "netpbm_internal.h"

t_netpbm_image	read_ppm_binary(int fd, int *status)
{
	t_netpbm_image	res;
	unsigned char	rgb[3];
	size_t			maxval;
	size_t			i;

	res.image_data = NULL;
	if (read_meta(fd, &res.width, &res.height, &maxval))
		*status = FILE_ERROR;
	else
	{
		if (res.width && res.height && maxval == 255)
		{
			*status = 0;
			res = form_image(res.width, res.height);
			i = -1;
			while (++i < res.width * res.height && read(fd, rgb, 3) > 0)
				res.image_data[i] =
					((int)rgb[0] << 16) | ((int)rgb[1] << 8) | ((int)rgb[2]);
		}
		else
			*status = FILE_ERROR;
	}
	return (res);
}
