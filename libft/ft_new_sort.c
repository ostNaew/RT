/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:32:12 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:32:13 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_sort_data		ft_new_sort(int (*compare)(const void *e1, const void *e2,
	size_t size), void (*swap)(void *e1, void *e2, size_t size), size_t size)
{
	t_sort_data res;

	res.compare = compare;
	res.swap = swap;
	res.size = size;
	return (res);
}
