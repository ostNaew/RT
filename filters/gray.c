/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gray.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:21:13 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/17 15:13:20 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filters.h"

t_vector	gray_scale(t_vector *colors, size_t size)
{
	double		color;
	t_vector	res;

	(void)size;
	color = (colors[0].x + colors[0].y + colors[0].z) / 3;
	res.x = color;
	res.y = color;
	res.z = color;
	return (res);
}
