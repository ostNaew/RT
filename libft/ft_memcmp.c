/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:48:58 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/21 15:45:25 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*c1;
	const unsigned char	*c2;

	i = -1;
	c1 = s1;
	c2 = s2;
	while (++i < n)
		if (c1[i] != c2[i])
			return (c1[i] - c2[i]);
	return (0);
}
