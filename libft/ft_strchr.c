/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:49:00 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/24 16:48:41 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	i = -1;
	if (s[0] == (char)c)
		return ((char *)s);
	while (s[++i])
		if (s[i + 1] == (char)c)
			return ((char *)s + i + 1);
	return (NULL);
}
