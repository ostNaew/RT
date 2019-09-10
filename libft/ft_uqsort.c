/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uqsort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:30:37 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/20 16:31:45 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	partition(void *arr, long start, long end,
	t_sort_data *d)
{
	void	*pivot;
	long	i;
	long	j;
	long	mid;

	mid = (start + end) / 2;
	if (d->compare(arr + (mid * d->size), arr + (start * d->size), d->size) < 0)
		d->swap(arr + (mid * d->size), arr + (start * d->size), d->size);
	if (d->compare(arr + (end * d->size), arr + (start * d->size), d->size) < 0)
		d->swap(arr + (end * d->size), arr + (start * d->size), d->size);
	if (d->compare(arr + (end * d->size), arr + (mid * d->size), d->size) < 0)
		d->swap(arr + (end * d->size), arr + (mid * d->size), d->size);
	d->swap(arr + (end * d->size), arr + (mid * d->size), d->size);
	pivot = arr + (end * d->size);
	i = start - 1;
	j = start - 1;
	while (++j <= end - 1)
		if (d->compare(arr + (j * d->size), pivot, d->size) < 0)
		{
			++i;
			d->swap(arr + (i * d->size), arr + (j * d->size), d->size);
		}
	d->swap(arr + ((i + 1) * d->size), arr + (end * d->size), d->size);
	return (i + 1);
}

static void	quick_sort(void *array, long start, long end, t_sort_data *data)
{
	long index;

	if (start < end)
	{
		index = partition(array, start, end, data);
		quick_sort(array, start, index - 1, data);
		quick_sort(array, index + 1, end, data);
	}
}

void		ft_uqsort(void *array, size_t amount, t_sort_data data)
{
	if (data.swap == NULL)
		data.swap = ft_uswap;
	if (data.compare == NULL)
		data.compare = ft_memcmp;
	if (array && amount && data.size)
		quick_sort(array, 0, (long)amount - 1, &data);
}
