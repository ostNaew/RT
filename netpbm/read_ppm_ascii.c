/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ppm_ascii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 17:01:01 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/13 16:17:44 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "netpbm_internal.h"

t_netpbm_image	read_ppm_ascii(int fd, int *status)
{
	t_netpbm_image	res;

	(void)fd;
	res.image_data = NULL;
	*status = FILE_ERROR;
	return (res);
}
