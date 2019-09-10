/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:39:04 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/21 16:06:37 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t nlen;

	i = -1;
	nlen = ft_strlen(needle);
	while (haystack[++i] && *needle)
		if (ft_memcmp(haystack + i, needle, nlen) == 0)
			return ((char *)haystack + i);
	return ((*needle) ? NULL : (char *)haystack);
}
