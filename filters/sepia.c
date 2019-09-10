/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:44:25 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/17 15:13:59 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filters.h"

t_vector	sepia_scale(t_vector *colors, size_t size)
{
	t_vector	res;

	(void)size;
	res.x = colors[0].x * 0.393 + colors[0].y * 0.769 + colors[0].z * 0.189;
	if (res.x > 1)
		res.x = 1;
	res.y = colors[0].x * 0.349 + colors[0].y * 0.686 + colors[0].z * 0.168;
	if (res.y > 1)
		res.y = 1;
	res.z = colors[0].x * 0.272 + colors[0].y * 0.534 + colors[0].z * 0.131;
	if (res.z > 1)
		res.z = 1;
	return (res);
}
