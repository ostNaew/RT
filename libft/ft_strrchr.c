/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:52:26 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/21 19:25:54 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t i;

	i = -1;
	while (s[++i])
		;
	if ((char)c == '\0')
		return ((char *)s + i);
	while (i > 0)
		if (s[i - 1] == (char)c)
			return ((char *)s + i - 1);
		else
			--i;
	return (NULL);
}
