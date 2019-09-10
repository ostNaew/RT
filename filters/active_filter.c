/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active_filter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:31:25 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/17 15:37:59 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filters.h"

t_filter	active_filter(size_t i, int resize)
{
	static t_filter	array[SIZE] = {
			(t_filter){NULL, 1},
			(t_filter){gray_scale, 1},
			(t_filter){sepia_scale, 1},
			(t_filter){negative_scale, 1},
			(t_filter){blur, 3},
			(t_filter){median, 3}};
	static size_t	index;

	if (i == 0)
	{
		if ((resize == -2 && array[index].size > 1) || resize == 2)
			array[index].size += resize;
		return (array[index]);
	}
	else if (i >= SIZE)
		index = 0;
	else
		index = index == i ? 0 : i;
	return (array[index]);
}
