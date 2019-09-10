/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:54:01 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/17 15:13:50 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filters.h"

t_vector	negative_scale(t_vector *colors, size_t size)
{
	t_vector	res;

	(void)size;
	res.x = 1. - colors[0].x;
	res.y = 1. - colors[0].y;
	res.z = 1. - colors[0].z;
	return (res);
}
