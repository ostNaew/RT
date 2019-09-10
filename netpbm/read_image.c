/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:38:37 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/14 20:26:20 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "netpbm_internal.h"

t_netpbm_image	read_image(const char *file, int *status)
{
	t_netpbm_image	res;
	char			buf[2];
	int				fd;

	res.image_data = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		*status = FILE_ERROR;
		return (res);
	}
	read(fd, buf, 2);
	if (ft_strnequ(buf, "P3", 2))
		res = read_ppm_ascii(fd, status);
	else if (ft_strnequ(buf, "P6", 2))
		res = read_ppm_binary(fd, status);
	else
		*status = INVALID_FORMAT;
	close(fd);
	return (res);
}
