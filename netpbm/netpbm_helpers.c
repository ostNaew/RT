/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 17:06:02 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/02/28 20:43:36 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "netpbm_internal.h"

t_netpbm_image	form_image(size_t width, size_t height)
{
	t_netpbm_image	res;

	res.image_data = ft_memalloc(sizeof(int) * width * height);
	res.width = width;
	res.height = height;
	return (res);
}

t_netpbm_image	new_image(void)
{
	return ((t_netpbm_image){
			.image_data = NULL,
			.width = 0,
			.height = 0});
}
