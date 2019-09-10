/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:35:06 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/08 14:17:35 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < n / sizeof(unsigned long) && dst != src)
		((unsigned long *)dst)[i] = ((unsigned long *)src)[i];
	j = i * sizeof(unsigned long);
	i = -1;
	while (++i + j < n && dst != src)
		((unsigned char *)dst)[i + j] = ((unsigned char *)src)[i + j];
	return (dst);
}
