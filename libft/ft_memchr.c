/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:28:10 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/21 20:36:30 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*arr;
	unsigned char		sym;
	size_t				i;

	i = -1;
	arr = s;
	sym = c;
	while (++i < n)
		if (arr[i] == sym)
			return ((void *)arr + i);
	return (NULL);
}
