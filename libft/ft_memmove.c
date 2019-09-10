/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:20:21 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/21 19:44:22 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (src > dst)
		ft_memcpy(dst, src, len);
	else
	{
		++len;
		d = dst;
		s = src;
		while (--len)
			d[len - 1] = s[len - 1];
	}
	return (dst);
}
