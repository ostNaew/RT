/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_from_pixel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:35:43 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/17 15:13:09 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filters.h"

t_vector	get_color_from_pixel(t_pixel pixel)
{
	if (pixel.divider == 0)
		return ((t_vector){0, 0, 0, 0});
	if (pixel.divider == 1)
		return (pixel.color);
	return (vector_scalar_mul(pixel.color, 1. / (double)pixel.divider));
}
