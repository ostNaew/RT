/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:05:05 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/23 15:20:56 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	sym;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	sym = (unsigned char)c;
	while (i < n && s[i] != sym)
	{
		d[i] = s[i];
		++i;
	}
	if (i != n)
	{
		d[i] = sym;
		return ((void *)(d + i + 1));
	}
	return (NULL);
}
