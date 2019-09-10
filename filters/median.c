/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   median.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:51:41 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/17 15:13:42 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filters.h"

int			compare(const void *e1, const void *e2, size_t size)
{
	t_vector	v1;
	t_vector	v2;

	v1 = *((t_vector*)e1);
	v2 = *((t_vector*)e2);
	(void)size;
	if ((v1.x + v1.y + v1.z) - (v2.x + v2.y + v2.z) < 0)
		return (-1);
	return (0);
}

t_vector	median(t_vector *colors, size_t size)
{
	t_sort_data	data;

	data = ft_new_sort(compare, NULL, sizeof(t_vector));
	ft_uqsort((void*)colors, size * size, data);
	return (colors[size * size / 2]);
}
