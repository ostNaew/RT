/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:44:32 by ajaehaer          #+#    #+#             */
/*   Updated: 2018/11/21 16:59:02 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char *res;

	res = ft_strstr(haystack, needle);
	res = res + ft_strlen(needle) > haystack + len ? NULL : res;
	return (*needle ? res : (char *)haystack);
}
