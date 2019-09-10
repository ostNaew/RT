/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:35:09 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/24 16:48:25 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (i < size)
	{
		if (j + i < size)
			ft_memcpy(dst + i, src, j + 1);
		else
		{
			ft_memcpy(dst + i, src, size - i - 1);
			dst[size - 1] = '\0';
		}
	}
	return ((size < i ? size : i) + j);
}
