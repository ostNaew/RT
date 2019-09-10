/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:03:22 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/21 20:58:44 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	size_t			j;
	unsigned long	f;

	i = -1;
	((unsigned char *)(&f))[0] = (unsigned char)c;
	((unsigned char *)(&f))[1] = (unsigned char)c;
	((unsigned char *)(&f))[2] = (unsigned char)c;
	((unsigned char *)(&f))[3] = (unsigned char)c;
	((unsigned char *)(&f))[4] = (unsigned char)c;
	((unsigned char *)(&f))[5] = (unsigned char)c;
	((unsigned char *)(&f))[6] = (unsigned char)c;
	((unsigned char *)(&f))[7] = (unsigned char)c;
	while (++i < len / 8)
		((unsigned long *)b)[i] = f;
	j = i * 8;
	i = -1;
	while (++i + j < len)
		((unsigned char *)b)[i + j] = (unsigned char)c;
	return (b);
}
